// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592270 rf_vfile_try_configured_optical_path
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall VFile, filename and numeric root id. Builds configured optical-media path into receiver+5 with unbounded57B6B0, writes root id+0 and clears packed-member DWORD+264 before stat. Stat success sets resolved byte+4=1 and returns AL1; stat failure returns0 WITHOUT clearing previously set resolved byte. Does not select/discover optical drive, inspect file type, open stream or update media byte+268; no root/path capacity checks.
char __thiscall rf_vfile_try_configured_optical_path(char *this, const char *a2, int a3)
{
  struct _stat64i32 Stat; // [esp+4h] [ebp-30h] BYREF

  rf_vfile_build_optical_media_path_unbounded(a3, a2, this + 5);
  *(_DWORD *)this = a3;
  *((_DWORD *)this + 66) = 0;
  if ( rf_vfile_optical_path_stat_adapter(this + 5, &Stat) )
    return 0;
  *(this + 4) = 1;
  return 1;
}

