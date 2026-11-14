// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ED7A0 rf_tan_float_core
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl F32 angle plainRET. FLD input, call x87 __CItan, FSTP F32local then FLD same local, returnST0. Single-precision rounded tangent via floating ABI; no degree conversion, finite/pole guard or extra scaling. Wrapper4ED780 forwards result. Spot setter527D32 uses this tangent of half outerangle before multiplying by range; previous cosine-extent annotation was wrong.
double __cdecl rf_tan_float_core(float a1)
{
  return (float)tan(a1);
}

