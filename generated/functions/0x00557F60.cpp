// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557F60 rf_geomod_vertex_pool_capacity_guard
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Returns0x40000000 through shared guard; no vertex pool capacity/free-count query or allocation.
int rf_geomod_vertex_pool_capacity_guard()
{
  return rf_geomod_pool_capacity_guard_constant();
}

