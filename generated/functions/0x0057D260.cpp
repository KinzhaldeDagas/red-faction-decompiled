// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D260 rf_path_probe_directory_by_temporary_chdir
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl candidate path, AL boolean. Saves current directory via _getcwd(local260,255) but ignores return. Calls57D0E0 candidate; nonzero status returnsfalse. On success calls57D0E0 saved path and ignores restoration status, returns true even if process directory fails to restore. Not a pure stat/existence predicate: mutates process drive/current directory, inherits lowercasing and unbounded260-byte input copy, and failed getcwd can leave saved path uninitialized.
char __cdecl rf_path_probe_directory_by_temporary_chdir(const char *candidate_path)
{
  char DstBuf[260]; // [esp+4h] [ebp-108h] BYREF

  _getcwd(DstBuf, 255);
  if ( rf_path_change_directory_with_drive_status((char *)candidate_path) )
    return 0;
  rf_path_change_directory_with_drive_status(DstBuf);
  return 1;
}

