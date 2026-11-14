// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00456FF0 rf_localtime64_adapter_456ff0
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one pointer slot. Pushes input unchanged to distinct607E57 (__localtime64), removes4 outgoing bytes and forwards EAX pointer. Plain RET leaves incoming
// argument for caller cleanup. No own null/time-range check, struct copy, allocation, synchronization or independent return normalization. Conversion, error behavior and returned
// storage ownership remain callee-owned; body does not implement them.
struct tm *__cdecl rf_localtime64_adapter_456ff0(__time64_t *Time)
{
  return _localtime64(Time);
}

