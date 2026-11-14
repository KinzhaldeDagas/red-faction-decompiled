// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592660 rf_vfile_loose_name_hash15
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl NUL-terminated byte string. Starts h=0; for each UNSIGNED byte computes h=((h+byte)*127)&0x7FFF using32-bit arithmetic; returns0..32767. Empty string hashes0, no case folding or separator normalization; wrapper592550 lowercases before exact-name lookup5925C0. Matches32768-head table1BA1F00. Decompiler short intermediate is not a signed-byte hash; raw MOVZX at592678 and AND7FFF at592690 establish unsigned byte and15-bit range. No NULL or length bound.
int __cdecl rf_vfile_loose_name_hash15(_BYTE *a1)
{
  int v2; // [esp+0h] [ebp-4h]
  __int16 v3; // [esp+0h] [ebp-4h]

  v2 = 0;
  while ( *a1 )
  {
    v3 = 127 * (v2 + (unsigned __int8)*a1++);
    v2 = v3 & 0x7FFF;
  }
  return v2;
}

