// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061799E crt_install_cxx_unhandled_exception_filter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed args. Push fixed __CxxUnhandledExceptionFilter callback, call imported SetUnhandledExceptionFilter with stdcall cleanup, then XOR EAX,EAX and
// return0. Discards old-filter pointer, no own error/once/restore guard or filter invocation. Does not preserve previous filter for later restoration in this body.
int crt_install_cxx_unhandled_exception_filter()
{
  SetUnhandledExceptionFilter(__CxxUnhandledExceptionFilter);
  return 0;
}

