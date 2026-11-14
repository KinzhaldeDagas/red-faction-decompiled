// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004108E0 rf_sin_float
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one stack float. FLD input then FSTP a32-bit outgoing slot and call410900; caller removes4 bytes and forwards ST0 without another result store.
// Fresh410900 calls __CIsin with x87 input, stores result to32-bit float local and reloads ST0 before returning. Thus sine has an explicit binary32 result boundary despite stored IDA
// double type. No argument reduction, domain/error policy, or finite-value guard is implemented in this outer wrapper; generic math adapter retains library classification.
double __cdecl rf_sin_float(float a1)
{
  return sub_410900(a1);
}

