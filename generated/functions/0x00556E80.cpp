// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556E80 rf_geomod_spatial_node_allocate
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): No incoming receiver or stack argument is used: incoming ECX is overwritten by global pool address before first call. Correct ABI is cdecl(void). Allocates40-byte spatial node, clears children32/36, resets intrusive face-list head/tail24/28. Bounds0..23 remain uninitialized. Raw allocator can returnNULL when exhausted/spill-disabled, but this wrapper dereferences unconditionally.
void *__cdecl rf_geomod_spatial_node_allocate()
{
  _DWORD *raw; // [esp+0h] [ebp-4h]

  raw = rf_geomod_spatial_node_pool_allocate_raw(rf_geomod_spatial_node_pool_descriptor);
  raw[9] = 0;
  raw[8] = 0;
  rf_intrusive_list_reset_head_tail(raw + 6);
  return raw;
}

