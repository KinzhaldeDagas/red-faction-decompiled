"""Verify published evidence and optionally the user's own Windows RF.exe."""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys


ROOT = Path(__file__).resolve().parents[1]


def require(condition, message):
    if not condition:
        raise ValueError(message)


def sha256(path):
    digest = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            digest.update(block)
    return digest.hexdigest()


def read_json(relative):
    return json.loads((ROOT / relative).read_text(encoding='utf-8'))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe', type=Path, help='Read-only path to your reference RF.exe')
    args = parser.parse_args()
    manifest = read_json('PUBLICATION_SHA256.json')
    for relative, expected in manifest.items():
        path = ROOT / relative
        require(path.resolve().is_relative_to(ROOT), 'Path escapes repository: ' + relative)
        require(not path.is_symlink() and path.is_file(), 'Missing file: ' + relative)
        require(sha256(path) == expected, 'Published hash mismatch: ' + relative)

    inventory = read_json('generated/function_inventory.json')
    successful = [row for row in inventory if row['decompiled']]
    native_only = [row for row in inventory if not row['decompiled']]
    require(len(inventory) == 7164 and len(successful) == 7155 and len(native_only) == 9,
            'Unexpected function inventory counts')
    for row in successful:
        path = ROOT / row['source']
        require(path.resolve().parent == ROOT / 'generated/functions', 'Unexpected source path')
        require(sha256(path) == row['source_sha256'], 'Function source hash mismatch: ' + row['ea'])
    require({p.name for p in (ROOT / 'generated/functions').iterdir()} ==
            {Path(row['source']).name for row in successful}, 'Function directory differs from inventory')
    require({p.name for p in (ROOT / 'generated/native_only').iterdir()} ==
            {Path(row['native_source']).name for row in native_only}, 'Native-only directory differs from inventory')
    report = read_json('analysis/export_report.json')
    require(sha256(ROOT / 'generated/rf_decompiled.c') == report['combined_source_sha256'],
            'Combined source hash mismatch')
    print(f'PASS: {len(manifest)} published hashes; 7,155 pseudocode functions; nine assembly-only functions.')
    if args.exe is None:
        print('Executable comparison skipped. Supply --exe with your own reference RF.exe to check native bytes.')
        return

    require(sha256(args.exe) == report['reference_executable_sha256'],
            'Executable SHA-256 differs from the reference version')
    data = args.exe.read_bytes()
    require(data[:2] == b'MZ', 'Not a DOS/PE executable')
    pe = struct.unpack_from('<I', data, 0x3C)[0]
    require(data[pe:pe + 4] == b'PE\0\0', 'Missing PE signature')
    machine, sections = struct.unpack_from('<HH', data, pe + 4)
    optional_size = struct.unpack_from('<H', data, pe + 20)[0]
    optional = pe + 24
    require(machine == 0x14C and struct.unpack_from('<H', data, optional)[0] == 0x10B,
            'Expected i386 PE32')
    image_base = struct.unpack_from('<I', data, optional + 28)[0]
    section_table = optional + optional_size
    ranges = []
    for index in range(sections):
        entry = section_table + index * 40
        _, rva, raw_size, raw_offset = struct.unpack_from('<IIII', data, entry + 8)
        require(raw_offset + raw_size <= len(data), 'Section outside file')
        ranges.append((image_base + rva, raw_size, raw_offset))

    def check_bytes(address, value):
        ea, expected = int(address, 16), bytes.fromhex(value)
        for start, size, offset in ranges:
            if start <= ea and ea + len(expected) <= start + size:
                actual = data[offset + ea - start:offset + ea - start + len(expected)]
                require(actual == expected, 'Executable byte mismatch at ' + address)
                return
        raise ValueError('Native range is outside file-backed PE sections: ' + address)

    functions = chunks = instructions = 0
    addresses = set()
    with (ROOT / 'generated/native_functions.jsonl').open(encoding='utf-8') as stream:
        for line in stream:
            row = json.loads(line)
            require(row['ea'] not in addresses, 'Duplicate native function')
            addresses.add(row['ea'])
            functions += 1
            for chunk in row['chunks']:
                require(int(chunk['end'], 16) - int(chunk['start'], 16) == len(bytes.fromhex(chunk['bytes'])),
                        'Native chunk length mismatch')
                check_bytes(chunk['start'], chunk['bytes'])
                chunks += 1
            for instruction in row['instructions']:
                check_bytes(instruction['ea'], instruction['bytes'])
                instructions += 1
    require(addresses == {row['ea'] for row in inventory}, 'Native functions differ from inventory')
    historical = read_json('analysis/export_verification.json')
    require(chunks == historical['native_chunks_original_PE_verified'] and
            instructions == historical['native_instructions_original_PE_verified'],
            'Native coverage differs from historical verification')
    print(f'PASS: user-supplied i386 PE32 RF.exe; {functions} functions, {chunks} chunks, {instructions} instructions match.')


if __name__ == '__main__':
    try:
        main()
    except (ValueError, OSError, KeyError, struct.error) as error:
        print('FAIL: ' + str(error), file=sys.stderr)
        sys.exit(1)
