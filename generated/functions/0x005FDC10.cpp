// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FDC10 rf_jpeg_error_exit_default
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jerror.c:error_exit matched): Fatalcallback:err.output_message+8(cinfo),jpeg_destroy0x5FF320,exit(1). No longjmp/recovery indefaultimplementation;applicationsmayoverrideerr.error_exit. Does not return. ExistingHexRaysnoreturnmatchesexit.
void __cdecl __noreturn rf_jpeg_error_exit_default(int a1)
{
  (*(void (__cdecl **)(int))(*(_DWORD *)a1 + 8))(a1);
  rf_jpeg_destroy(a1);
  exit(1);
}

