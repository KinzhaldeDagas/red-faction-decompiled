// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FDE60 rf_jpeg_reset_error_mgr
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jerror.c:reset_error_mgr matched): Setsnum_warnings108=0,msg_code20=0. Preservestrace_level,callbacks,tables andparameters. Noallocationorstreamwork;APIvoid.
int __cdecl rf_jpeg_reset_error_mgr(int *a1)
{
  int result; // eax

  *(_DWORD *)(*a1 + 108) = 0;
  result = *a1;
  *(_DWORD *)(*a1 + 20) = 0;
  return result;
}

