// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557F30 rf_geomod_vertex_pool_optional_noop_hook
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): If global1809818 nonzero, passes vertex pool descriptor in ECX to zero-return no-op4BE0E0. Disabled path leaves EAX unspecified. No pool reset/statistics update occurs.
void __cdecl rf_geomod_vertex_pool_optional_noop_hook()
{
  if ( dword_1809818 )
    rf_hook_4BE0E0_return_zero();
}

