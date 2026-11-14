// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557FE0 rf_geomod_pool_capacity_guard_constant
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Unconditionally returns0x40000000; no memory reads, receiver dependency, free-space accounting or reservation. Used by fixed-pool reserve/threshold wrappers.
int rf_geomod_pool_capacity_guard_constant()
{
  return 0x40000000;
}

