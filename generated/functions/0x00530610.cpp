// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530610 rf_geomod_face_pool_take_peak_used_count
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): No args. Pass global96-byte face-pool descriptor as ECX to536290, return PEAK active count since previous query, and reset stored peak to CURRENT active count as a side effect. Not a current-count getter or free-capacity query. Old function name/short comment and Boolean initializer telemetry wording corrected.
int rf_geomod_face_pool_take_peak_used_count()
{
  return rf_geomod_face_pool_take_peak_and_reset(rf_geomod_face_pool_descriptor);
}

