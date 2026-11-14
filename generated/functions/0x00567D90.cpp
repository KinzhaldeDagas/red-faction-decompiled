// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567D90 rf_float_value_near_ref_strict
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): cdecl(value,floatRef). Float-rounds d=value-*ref,tests strict open epsilon interval(+/-9.999999747378752e-5). Boundary equality and NaN returnfalse. Does not dereference first value as pointer or modify storage.
unsigned __int8 __cdecl rf_float_value_near_ref_strict(float value, const float *ref)
{
  float v4; // [esp+4h] [ebp-4h]

  v4 = value - *ref;
  return v4 < 0.00009999999747378752 && v4 > -0.00009999999747378752;
}

