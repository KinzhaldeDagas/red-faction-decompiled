// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567DE0 rf_float_refs_near_strict
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): cdecl(leftRef,rightRef). Float d=*left-*right;returnsbyte1 only if d<epsilon ANDd>-epsilon,epsilon9.999999747378752e-5. Neither equal-boundary nor NaN is near. No null/finite guard.
unsigned __int8 __cdecl rf_float_refs_near_strict(const float *left, const float *right)
{
  float v4; // [esp+4h] [ebp-4h]

  v4 = *left - *right;
  return v4 < 0.00009999999747378752 && v4 > -0.00009999999747378752;
}

