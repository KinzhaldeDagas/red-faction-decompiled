// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D509 crt_dword_is_nonzero_bool
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime EH predicate, KEEP library flag. Cdecl one rawDWORD argument; return canonical fullEAX1 iff argument!=0, else0. No dereference,
// sign/range/type interpretation, allocation, helper call or global writes. Existing catch-object/handler callers establish runtime context; no game-owned classification from generic
// Boolean behavior. MOV EDI,EDI prologue leavesEDI unchanged.
BOOL __cdecl crt_dword_is_nonzero_bool(int a1)
{
  return a1 != 0;
}

