// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A428 ___crtExitProcess
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl exit code. First call crtCorExitProcess(code), discard argument; if it returns, call imported ExitProcess(SAME code). No return instruction or own
// handler-table walk here. Existing noreturn type retained; managed/native termination policy and side effects delegated, no error-result normalization.
void __cdecl __noreturn __crtExitProcess(UINT uExitCode)
{
  __crtCorExitProcess(uExitCode);
  ExitProcess(uExitCode);
}

