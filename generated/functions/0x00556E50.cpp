// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556E50 rf_geomod_spatial_node_pool_capacity_guard
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Returns shared literal0x40000000 capacity guard; no pool state/free-count inspection and no allocation.
int rf_geomod_spatial_node_pool_capacity_guard()
{
  return rf_geomod_pool_capacity_guard_constant();
}

