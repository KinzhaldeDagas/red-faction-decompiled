// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530620 rf_geomod_face_pool_capacity_guard
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): No args. Call557FE0 and return literal0x40000000. No face pool descriptor/counter read, reservation or allocation; ignores current exhaustion. Used by legacy reserve comparisons, not a cumulative geometry limit.
int rf_geomod_face_pool_capacity_guard()
{
  return rf_geomod_pool_capacity_guard_constant();
}

