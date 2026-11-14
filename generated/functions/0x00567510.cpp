// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567510 rf_sqrt_fast_lookup_refine_once
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): stdcall(float x),RET4. Seed y has bits=table1806938[(bits(x)>>14)&1023] OR (((exponentBits+3F800000)>>1)&7F800000). Returns float(0.5*y*(3-y*y/x)) throughST0,one square-root Newton correction. No zero/domain/finite guard; division byx still executes for0. Does not initialize table or preserve input sign in seed.
double __stdcall rf_sqrt_fast_lookup_refine_once(float x)
{
  float v2; // [esp+4h] [ebp-8h]

  LODWORD(v2) = dword_1806938[(LODWORD(x) >> 14) & 0x3FF]
              | (((LODWORD(x) & 0x7F800000u) + 1065353216) >> 1) & 0x7F800000;
  return (float)((3.0 - v2 * v2 / x) * v2 * 0.5);
}

