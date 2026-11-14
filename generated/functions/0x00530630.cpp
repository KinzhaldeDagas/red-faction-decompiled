// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530630 rf_geomod_corner_pool_take_peak_used_count
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): No args. Call536410 with global28-byte corner-pool descriptor ECX, return PEAK active count since last query then reset stored peak to CURRENT count. Not a pure current usage getter. Queries themselves alter subsequent telemetry.
int rf_geomod_corner_pool_take_peak_used_count()
{
  return rf_geomod_corner_pool_take_peak_and_reset(rf_geomod_corner_pool_descriptor);
}

