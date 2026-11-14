// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057CF20 rf_vfile_unlink_loose_file_after_reset_attributes
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl filename and numeric root id. Requires57CE90 stat-exists success, rebuilds loose path into516-byte local, calls SetFileAttributesA(path,0x80 NORMAL) and ignores result, then returns AL(_unlink(path)==0). Failed unlink can leave attributes changed. Directories can pass stat gate but unlink normally fails. Rejects special ids through stat helper; no VPP deletion, path-size guard or rollback.
bool __cdecl rf_vfile_unlink_loose_file_after_reset_attributes(const char *a1, char *a2)
{
  CHAR FileName[516]; // [esp+0h] [ebp-208h] BYREF

  if ( !rf_vfile_loose_path_stat_exists(a1, a2) )
    return 0;
  rf_vfile_build_loose_path((int)a2, a1, FileName);
  SetFileAttributesA(FileName, 0x80u);
  return _unlink(FileName) == 0;
}

