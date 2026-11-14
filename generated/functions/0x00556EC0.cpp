// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556EC0 rf_geomod_spatial_tree_destroy_recursive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Requires nonnull root; recursively releases child32 then child36 if present, finally pushes current40-byte node onto pool free list. Does not destroy faces, walk face list, clear Face72 reciprocal owner pointers, or repair external root references. No cycle/depth guard; release overwrites first DWORD with freelist link.
_DWORD *__cdecl rf_geomod_spatial_tree_destroy_recursive(_DWORD *a1)
{
  if ( a1[8] )
    rf_geomod_spatial_tree_destroy_recursive(a1[8]);
  if ( a1[9] )
    rf_geomod_spatial_tree_destroy_recursive(a1[9]);
  return rf_geomod_spatial_node_pool_release_raw(rf_geomod_spatial_node_pool_descriptor, a1);
}

