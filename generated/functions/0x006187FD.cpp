// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006187FD __statfp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No C arguments. FSTSW localWORD (waiting form),MOVSX signed16 status intoEAX,LEAVE/RET. Reads CURRENT hardware x87 status,not a caller fpstat argument.
// Returns sign-extended statusDWORD; does not clear exception flags or modify CW. Corrected ordinary no-arg ABI.
int __cdecl _statfp()
{
  __int16 v0; // fps

  return v0;
}

