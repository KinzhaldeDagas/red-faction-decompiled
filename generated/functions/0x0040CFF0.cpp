// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040CFF0 rf_sqrt_float
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one stack float. FLD input then FSTP a32-bit outgoing slot and call40D010; caller removes4 bytes and forwards x87 ST0 without another result store.
// Fresh40D010 loads the float, calls __CIsqrt, FSTPs result to32-bit local then reloads ST0: returned value has this explicit binary32 rounding boundary although stored IDA type is
// double. Does not add domain/NaN checks or error translation; those remain helper-owned. Generic math adapter retains library classification.
double __cdecl rf_sqrt_float(float a1)
{
  return sub_40D010(a1);
}

