// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530640 rf_geomod_corner_pool_capacity_guard
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): No args, call557FE0 and return0x40000000. Does not inspect corner free list/count, reserve records or account used peaks.
int rf_geomod_corner_pool_capacity_guard()
{
  return rf_geomod_pool_capacity_guard_constant();
}

