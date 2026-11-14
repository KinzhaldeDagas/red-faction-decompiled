// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605B37 ?_UnwindNestedFrames@@YGXPAUEHRegistrationNode@@PAUEHExceptionRecord@@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Stdcall(TargetFrame,ExceptionRecord), RET8; incoming
// EBX NOT an argument. Save current fs:0 record pointer in stack local BEFORE calling imported RtlUnwind(TargetFrame,own ReturnPoint605B62,ExceptionRecord,NULL ReturnValue). At
// return point clear ONLY flag mask2 in ExceptionRecord+4; read resulting fs:0, write that pointer into saved registration's first DWORD, then set fs:0=saved registration. Restore
// EDI/ESI/EBX/EBP, return. Thus reinsert saved guard after OS unwind; decompiler's incoming-EBX output pointer is phantom, saved local actually supplies it. Does not
// initialize/replace exception record, clear all unwind flags, walk chain itself, lock or validate inputs. No promised execution of return-point cleanup if OS unwind escapes/fails.
void __stdcall _UnwindNestedFrames(void *TargetFrame, struct EHExceptionRecord *ExceptionRecord)
{
  struct _EXCEPTION_REGISTRATION_RECORD **v2; // ebx

  RtlUnwind(TargetFrame, &_ReturnPoint_27112, (PEXCEPTION_RECORD)ExceptionRecord, nullptr);
  ExceptionRecord->ExceptionFlags &= ~2u;
  *v2 = NtCurrentTeb()->NtTib.ExceptionList;
}

