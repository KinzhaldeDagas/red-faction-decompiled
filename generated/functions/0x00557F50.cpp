// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557F50 rf_geomod_vertex_pool_take_peak_used_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Calls558140 on global44-byte vertex pool. Returns PEAK active count since previous query and resets stored peak to CURRENT active count. It is not a pure current usage getter.
int rf_geomod_vertex_pool_take_peak_used_count()
{
  return rf_geomod_vertex_pool_take_peak_and_reset(rf_geomod_vertex_pool_descriptor);
}

