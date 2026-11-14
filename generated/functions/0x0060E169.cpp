// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E169 ___crtTlsAlloc@4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Nine-byte stdcall adapter: CALL imported TlsAlloc with NO arguments, then RET4 discards one compatibility caller slot never read. Return TLS indexEAX
// unchanged. This is not a six-byte transparent JMP thunk; native call/cleanup is essential and existing library/thunk flags retained. No use of ignored slot as callback or TLS
// initialization value.
// attributes: thunk
DWORD __stdcall __crtTlsAlloc(int a1)
{
  return TlsAlloc();
}

