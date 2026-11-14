// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060ACA2 start
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Ten-byte CRT startup adapter. CALL security_init_cookie then TAIL JMP tmainCRTStartup; no own frame, argument read, application main call, normalized result
// or RET. Cookie establishment precedes startup delegate; original caller return address retained if delegate ever returns. Does not implement full runtime/main initialization
// itself.
int start()
{
  __security_init_cookie();
  return __tmainCRTStartup();
}

