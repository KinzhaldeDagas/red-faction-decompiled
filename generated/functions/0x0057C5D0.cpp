// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057C5D0 rf_vfile_create_registered_directory_chain
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl root id. Builds directory path via57B400 into260-byte local buffer, then returns57C610 recursive mkdir helper result, ordinarily0 even when mkdir fails. Root0 builder removes final data-root byte; invalid ids/empty roots and unbounded path copy inherit builder behavior. Does not enumerate or register files.
int __cdecl rf_vfile_create_registered_directory_chain(int a1)
{
  char *v1; // eax
  char v3[260]; // [esp+0h] [ebp-108h] BYREF

  v1 = rf_vfile_copy_loose_directory_cstring_unbounded(a1, v3);
  return rf_path_mkdir_backslash_chain_ignoring_errors(v1);
}

