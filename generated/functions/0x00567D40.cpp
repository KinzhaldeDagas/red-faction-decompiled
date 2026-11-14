// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567D40 rf_float_ref_near_value_strict
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): cdecl(floatRef,value). Float-rounds d=*ref-value,returns byte1 only when -float1e-4<d<float1e-4,strict both ends. NaN rejects. At exact +/-epsilon returnsfalse,as does corresponding far predicate; not inverse of inequality at boundaries.
unsigned __int8 __cdecl rf_float_ref_near_value_strict(const float *ref, float value)
{
  float v4; // [esp+4h] [ebp-4h]

  v4 = *ref - value;
  return v4 < 0.00009999999747378752 && v4 > -0.00009999999747378752;
}

