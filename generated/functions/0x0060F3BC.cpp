// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F3BC ___report_gsfailure
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Security-failure reporter, no semantic stack args;
// captures live registers into shared global context2021420 then invokes OS failure path. Save EAX/ECX/EDX/EBX/ESI/EDI into globals20214D0/CC/C8/C4/C0/BC. Store segment registers as
// WORDS at context offsets8Ch,90h,94h,98h,BCh,C8h, leaving upper16 bits unchanged. EBP field=previous EBP saved at own[EBP],EIP=own returnPC[EBP+4],ESP=&[EBP+8] (post-return
// stack),not current allocated stack. Captured EFLAGS come AFTER own SUB ESP328h, so arithmetic flags are frame-allocation flags, not original callsite flags. Does not capture
// floating/SSE/debug register state or zero whole context. Includes read of local DWORD EBp-320h not initialized by this routine, result discarded. Set
// contextFlagsDWORD2021420=10001h; exception record20213C8 codeC0000409,flags1,address=same returnPC. Other exception/context fields untouched; no whole record reset/parameter
// initialization. Original constant EXCEPTION_POINTERS64907C independently binds {20213C8,2021420}. Copy securityCookie664BD8/complement664BDC into two local stack DWORDs only; no
// cookie comparison or forwarded arguments. Call original PE KERNEL32 APIs: IsDebuggerPresent ->global2021418; call clear-global helper61D51B with ignored compatibility1
// (zeros2021E1C); SetUnhandledExceptionFilter(NULL) WITHOUT restoring previous handler; UnhandledExceptionFilter(&global pointers),IGNORE result. Re-read LIVE debugger global: if0
// call clear helper again. GetCurrentProcess,TerminateProcess(handle,C0000409),ignore returned Boolean. Existing noreturn policy typing retained, but actual native LEAVE/RET exists
// if TerminateProcess returns; no own failfast loop/abort fallback. No lock, thread-local snapshots, recursion guard, per-field atomicity or own SEH. Partial shared records can
// retain other/stale fields; do not infer full CONTEXT capture from pseudocode.
void __cdecl __noreturn __report_gsfailure()
{
  int v0; // eax
  int v1; // edx
  int v2; // ecx
  int v3; // ebx
  int v4; // edi
  int v5; // esi
  unsigned int v6; // kr00_4
  HANDLE CurrentProcess; // eax
  int vars0; // [esp+328h] [ebp+0h]
  _UNKNOWN *retaddr; // [esp+32Ch] [ebp+4h]
  char v10; // [esp+330h] [ebp+8h] BYREF

  unk_20214D0 = v0;
  unk_20214CC = v2;
  unk_20214C8 = v1;
  unk_20214C4 = v3;
  unk_20214C0 = v5;
  unk_20214BC = v4;
  unk_20214E8 = __SS__;
  unk_20214DC = __CS__;
  unk_20214B8 = __DS__;
  unk_20214B4 = __ES__;
  unk_20214B0 = __FS__;
  unk_20214AC = __GS__;
  v6 = __readeflags();
  unk_20214E0 = v6;
  unk_20214D4 = vars0;
  unk_20214D8 = retaddr;
  unk_20214E4 = &v10;
  unk_2021420 = 65537;
  unk_20213D4 = retaddr;
  unk_20213C8 = -1073740791;
  unk_20213CC = 1;
  unk_2021418 = IsDebuggerPresent();
  crt_clear_dword_02021e1c();
  SetUnhandledExceptionFilter(nullptr);
  UnhandledExceptionFilter((struct _EXCEPTION_POINTERS *)&ExceptionInfo);
  if ( !unk_2021418 )
    crt_clear_dword_02021e1c();
  CurrentProcess = GetCurrentProcess();
  TerminateProcess(CurrentProcess, 0xC0000409);
}

