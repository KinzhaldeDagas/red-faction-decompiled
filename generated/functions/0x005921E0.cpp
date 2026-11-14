// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005921E0 rf_vfile_try_direct_path
// UNREALRED VERIFIED [streaming-contract-20260829] Stats an already selected physical path (or one built from a registered root) and marks the VFile source valid only when that direct path exists.
char __thiscall rf_vfile_try_direct_path(void *this, const char *a2, int a3)
{
  struct _stat64i32 Stat; // [esp+4h] [ebp-30h] BYREF

  *((_DWORD *)this + 66) = 0;
  if ( a3 > -1 )
  {
    rf_vfile_build_loose_path(a3, a2, (char *)this + 5);
    *(_DWORD *)this = a3;
  }
  if ( rf_vfile_optical_path_stat_adapter((char *)this + 5, &Stat) )
    return 0;
  *((_BYTE *)this + 4) = 1;
  return 1;
}

