// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556E60 rf_geomod_spatial_node_pool_optional_noop_hook
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): If global1809818 nonzero, passes spatial pool descriptor in ECX to4BE0E0, whose instructions only return0 and ignore receiver. Disabled path leaves EAX unspecified. No pool/statistics reset or allocation occurs.
void __cdecl rf_geomod_spatial_node_pool_optional_noop_hook()
{
  if ( dword_1809818 )
    rf_hook_4BE0E0_return_zero();
}

