// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567ED0 rf_float_refs_far_strict
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): cdecl(leftRef,rightRef). Float d=*left-*right;returnsbyte1 iff d>epsilon ORd<-epsilon. Exact boundary and NaN false,so not complement of near567DE0. No pointer checks or relative-error scaling.
unsigned __int8 __cdecl rf_float_refs_far_strict(const float *left, const float *right)
{
  float v4; // [esp+4h] [ebp-4h]

  v4 = *left - *right;
  return v4 > 0.00009999999747378752 || v4 < -0.00009999999747378752;
}

