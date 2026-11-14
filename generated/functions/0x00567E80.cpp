// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567E80 rf_float_value_far_from_ref_strict
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): cdecl(value,floatRef). Float d=value-*ref,returnsbyte1 outside CLOSED epsilon band using strict greater/less tests. Exact boundary and NaN false. Not logical complement of567D90;no writes.
unsigned __int8 __cdecl rf_float_value_far_from_ref_strict(float value, const float *ref)
{
  float v4; // [esp+4h] [ebp-4h]

  v4 = value - *ref;
  return v4 > 0.00009999999747378752 || v4 < -0.00009999999747378752;
}

