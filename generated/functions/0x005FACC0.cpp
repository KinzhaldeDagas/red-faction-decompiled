// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FACC0 rf_time64_forward
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl time64 output pointer;directly forwards to _time64,returns its64-bit result. No conversion,local time formatting or validation;used for metadata file timestamp comparison.
__time64_t __cdecl rf_time64_forward(__time64_t *Time)
{
  return _time64(Time);
}

