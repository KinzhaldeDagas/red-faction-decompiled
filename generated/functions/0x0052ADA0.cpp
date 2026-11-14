// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052ADA0 rf_geomod_boolean_is_active
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): No args normalizedALbool from SIGNED globalstage>=0. Any nonnegative value including invalid>7 reports active; negative values reportfalse. No validation or progress. Normal inactive sentinel-1.
bool rf_geomod_boolean_is_active()
{
  return rf_geomod_boolean_stage >= 0;
}

