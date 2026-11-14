// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004108A0 rf_cos_float
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl oneF32 angle, plainRET floatingx87 result. FLD argument, round/store toF32 outgoing stack, call4108C0, then direct return without consumingST0. Core calls __CIcos,rounds toF32 local and reloads, so result is single-precision cosine carried viax87 double ABI, not logarithm or a double-precision cos result. Input directlyradians, no degree conversion or normalization.
double __cdecl rf_cos_float(float a1)
{
  return sub_4108C0(a1);
}

