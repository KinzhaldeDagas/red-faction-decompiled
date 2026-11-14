// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061795C ?__CxxUnhandledExceptionFilter@@YGJPAU_EXCEPTION_POINTERS@@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Stdcall(EXCEPTION_POINTERS*), LONG return, RET4. No
// NULL guards. If pointed EXCEPTION_RECORD codeE06D7363 AND NumberParameters3 AND parameter0 equals exact19930520h,19930521h,19930522h or IMMEDIATE01994000h, call terminate noreturn.
// Otherwise return0 (continue search). No forwarding previous filter, throw-object/ThrowInfo validation, parameter-pointer dereference or own exception handling.
LONG __stdcall __CxxUnhandledExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
  PEXCEPTION_RECORD ExceptionRecord; // eax
  void *v2; // eax

  ExceptionRecord = ExceptionInfo->ExceptionRecord;
  if ( ExceptionInfo->ExceptionRecord->ExceptionCode == -529697949 && ExceptionRecord->NumberParameters == 3 )
  {
    v2 = (void *)ExceptionRecord->ExceptionInformation[0];
    if ( v2 == (void *)429065504 || v2 == (void *)429065505 || v2 == (void *)429065506 || v2 == &unk_1994000 )
      terminate();
  }
  return 0;
}

