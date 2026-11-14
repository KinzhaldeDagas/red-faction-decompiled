// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567E30 rf_float_ref_far_from_value_strict
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): cdecl(floatRef,value). Float d=*ref-value;returnsbyte1 if d>epsilon ORd<-epsilon,strict. At exact +/-epsilon BOTH this far predicate and near567D40 arefalse. NaN/unordered returnsfalse,not true inequality. No pointer validation.
unsigned __int8 __cdecl rf_float_ref_far_from_value_strict(const float *ref, float value)
{
  float v4; // [esp+4h] [ebp-4h]

  v4 = *ref - value;
  return v4 > 0.00009999999747378752 || v4 < -0.00009999999747378752;
}

