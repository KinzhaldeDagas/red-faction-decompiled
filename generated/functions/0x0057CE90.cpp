// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057CE90 rf_vfile_loose_path_stat_exists
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl filename and root id (current prototype void pointer represents numeric id). Immediately returns ALfalse for decimal9999999 or9999998; otherwise builds loose path into516-byte local and calls57CF00 stat wrapper. Returns ALtrue iff stat==0, for directories as well as files. No VPP lookup, file-type filter, capacity/id validation or media probing.
bool __cdecl rf_vfile_loose_path_stat_exists(const char *a1, char *a2)
{
  struct _stat64i32 Stat; // [esp+0h] [ebp-238h] BYREF
  char FileName[516]; // [esp+30h] [ebp-208h] BYREF

  if ( a2 == byte_98967F || a2 == (char *)&unk_98967E )
    return 0;
  rf_vfile_build_loose_path((int)a2, a1, FileName);
  return rf_path_stat64i32_adapter(FileName, &Stat) == 0;
}

