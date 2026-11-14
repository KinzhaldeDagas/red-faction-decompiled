// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FDB80 rf_jpeg_std_error
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jerror.c:jpeg_std_error matched): Cdecl err-manager pointer,returns same. Installs callbacks0error_exit=5FDC10,4emit_message=5FDCA0,8output_message=5FDC40,12format_message=5FDD10,16reset_error_mgr=5FDE60. trace_level104=0,num_warnings108=0,msg_code20=0;message table112=0x648978,lastmessage116=123,addon table120=NULL,first/lastaddon124/128=0. Does notallocate,initializecinfo orsetmsgparameters24..103.
void (__cdecl __noreturn **__cdecl rf_jpeg_std_error(void (__cdecl __noreturn **a1)(int)))(int)
{
  *a1 = rf_jpeg_error_exit_default;
  a1[1] = (void (__cdecl __noreturn *)(int))rf_jpeg_emit_message_default;
  a1[2] = (void (__cdecl __noreturn *)(int))rf_jpeg_output_message_default;
  a1[3] = (void (__cdecl __noreturn *)(int))rf_jpeg_format_message_default;
  a1[4] = (void (__cdecl __noreturn *)(int))rf_jpeg_reset_error_mgr;
  a1[26] = nullptr;
  a1[27] = nullptr;
  a1[5] = nullptr;
  a1[28] = (void (__cdecl __noreturn *)(int))off_648978;
  a1[29] = (void (__cdecl __noreturn *)(int))123;
  a1[30] = nullptr;
  a1[31] = nullptr;
  a1[32] = nullptr;
  return a1;
}

