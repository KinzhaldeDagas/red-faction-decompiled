// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605CCB ?TranslatorGuardHandler@@YA?AW4_EXCEPTION_DISPOSITION@@PAUEHExceptionRecord@@PAUTranslatorGuardRN@@PAX2@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl translator guard, reads stack
// {exception*,40-byte guard*,context*}, any fourth dispatcher slot ignored; incoming EBX not an argument. CLD, verify guard+8 XOR guardAddress cookie. If exceptionFlags &66h: write
// DWORD1 at guard+36, return disposition1. Otherwise call InternalCxxFrameHandler(exception,guard+16 pointer,context,NULL,guard+12 FuncInfo,guard+20 depth,guard+24 marker,1
// recursive), ignore EAX. If guard+36 remains0, stdcall UnwindNestedFrames(guard,exception); then call raw translator helper605BF4 with seven caller-popped slots
// {0x123,&localContinuation,0,0,0,0,0}. Its sentinel branch publishes605C9F and returns1; no translator callback on this sentinel path. Load EAX=published
// continuation,EBX=guard,ESP=*(guard+28),EBP=*(guard+32), JMP EAX (nonlocal transfer, not callback CALL). Ordinary unwind-flag branch restores own EBX/frame and RET. Dead native
// fallback605D64 returns1 but no captured incoming branch. Guard+36 is unwind-observed marker, not destination PC. No own record/target validation or cleanup if delegate escapes.
// Corrected prototype removes phantom EBX receiver caused by earlier UnwindNestedFrames type.
enum _EXCEPTION_DISPOSITION __cdecl TranslatorGuardHandler(
        struct EHExceptionRecord *ExceptionRecord,
        _DWORD *TargetFrame,
        struct _CONTEXT *a3)
{
  enum _EXCEPTION_DISPOSITION (*v4)(void); // [esp+4h] [ebp-4h] BYREF

  crt_check_security_cookie_ecx((unsigned int)TargetFrame ^ TargetFrame[2]);
  if ( (ExceptionRecord->ExceptionFlags & 0x66) != 0 )
  {
    TargetFrame[9] = 1;
    return ExceptionContinueSearch;
  }
  else
  {
    __InternalCxxFrameHandler(
      ExceptionRecord,
      (struct EHRegistrationNode *)TargetFrame[4],
      a3,
      nullptr,
      (const struct _s_FuncInfo *)TargetFrame[3],
      TargetFrame[5],
      (struct EHRegistrationNode *)TargetFrame[6],
      1u);
    if ( !TargetFrame[9] )
      _UnwindNestedFrames(TargetFrame, ExceptionRecord);
    _CallSETranslator((struct EHExceptionRecord *)0x123, &v4, nullptr, nullptr, nullptr, 0, nullptr);
    return v4();
  }
}

