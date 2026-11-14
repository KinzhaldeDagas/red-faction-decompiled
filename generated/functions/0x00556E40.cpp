// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556E40 rf_geomod_spatial_node_pool_take_peak_used_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Calls557AC0 on global40-byte spatial-node pool. Returns PEAK active node count since previous query and resets stored peak to CURRENT active count; it is not a pure current-count getter. Wrapper has no arguments.
int rf_geomod_spatial_node_pool_take_peak_used_count()
{
  return rf_geomod_spatial_node_pool_take_peak_and_reset(rf_geomod_spatial_node_pool_descriptor);
}

