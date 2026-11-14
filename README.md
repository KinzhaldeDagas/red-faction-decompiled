# Red Faction Decompiled

IDA-based decompilation and reverse-engineering research of the original **32-bit Windows Red Faction executable (`RF.exe`)**. This repository publishes the Windows source evidence preserved in the verified backup from November 13, 2026, before the later platform translation work.

**Work in progress: the exported pseudocode is not yet buildable or playable.**

## Bring your own game files

You must supply your own legally obtained copy of Red Faction, including `RF.exe` and the original game data, for executable verification or any work that uses game resources. No game executable, DLL, VPP archive, level, texture, model, music, or sound files are included. IDA databases are also excluded because they can contain original executable bytes. Keep your installation outside this repository; `--exe` reads the supplied file without copying it here.

The reference Windows executable has SHA-256:

```text
f4d0df8ad062f99fd3fb4c858c66c4107e3629800d357499727af332142ea9f9
```

Other executable versions may have different addresses, layouts, and hashes.

## Contents

| Path | Contents |
| --- | --- |
| `generated/rf_decompiled.c` | Combined Hex-Rays pseudocode export |
| `generated/functions/` | 7,155 individual pseudocode functions, named by original address |
| `generated/native_only/` | Nine assembly listings where C decompilation failed |
| `generated/function_inventory.json` | All 7,164 known IDA functions, export status, and source hashes |
| `generated/rf_local_types.h` | Exported local type declarations |
| `generated/local_types_serialized.json` | Serialized evidence for 219 local types |
| `generated/ida_metadata_before.json` | Saved names, types, comments, and function chunks |
| `generated/temporary_in_memory_inference_delta.json` | Temporary inferred metadata changes observed during export |
| `generated/native_functions.jsonl` | Per-function disassembly, annotations, and instruction/chunk bytes for verification |
| `analysis/callgraph.json` | Recorded direct calls, jumps, and indirect-call sites |
| `analysis/windows_imports.json` | Original Windows imports and observed dynamic library/export strings |
| `analysis/export_report.json` | Export results with local input paths replaced by placeholders |
| `analysis/export_verification.json` | Historical export-integrity verification report |
| `analysis/provenance.json` | Backup identity, source hashes, and packaging changes |
| `PUBLICATION_SHA256.json` | SHA-256 hashes of published files |

The function inventory describes the known IDA functions, not every executable byte. The native listings and JSON evidence contain original code bytes as part of the reverse-engineering record; they are not a bundled game executable. Generated evidence is preserved byte-for-byte from the backup. The macOS port, build products, and third-party SDKs are outside this repository's scope.

## Verification

Python 3.9 or later is sufficient; no third-party Python packages are needed.

Check the published files and per-function source hashes:

```sh
python3 tools/verify_publication.py
```

Also compare every recorded native function chunk and instruction against your own reference executable:

```sh
python3 tools/verify_publication.py --exe "/path/to/your/Red Faction/RF.exe"
```

The historical verification report describes the original export and its original input hashes. Use `PUBLICATION_SHA256.json` for the current repository files, including the sanitized export report. File integrity and matching machine-code evidence do not establish that the pseudocode compiles or reproduces the executable's behavior.

## Current limitations

The combined export still depends on Windows headers, Hex-Rays definitions, recovered globals, and original PE32 object layouts. It contains nine explicit decompilation failure blocks. Per-function and combined exports can reflect different temporary inference passes; the saved metadata and inference delta are provided to make those differences inspectable. A Windows build and source-to-binary equivalence have not been established.

## Rights and attribution

Red Faction and third-party material remain the property of their respective rights holders. Original tool attribution notices are retained in generated files. This repository does not grant rights to the original game or third-party material and does not include a blanket open-source license for the decompiled code.
