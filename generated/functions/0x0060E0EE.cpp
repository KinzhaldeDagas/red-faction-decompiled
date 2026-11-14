// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E0EE __encoded_null
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Nine-byte no-argument wrapper. Push literalNULL, call60E07C encode-pointer helper, POP ECX to reclaim4 bytes, return EAX. Encoded-null value depends on
// selected provider/platform/identity fallback; not necessarily literal0 and not a fixed stored cookie. No allocation, global write or callback invocation beyond encoder delegation.
PVOID _encoded_null()
{
  return _encode_pointer(nullptr);
}

