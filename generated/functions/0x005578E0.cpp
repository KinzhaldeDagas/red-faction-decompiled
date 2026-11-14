// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005578E0 rf_room_spatial_tree_insert_unowned_faces
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): ECX EXISTING spatial root, stack room-face list. Always allocates a new node; collects faces with Face72==0 and non-liquid metadata40, traversing room link92, sets owner, computes bounds and recursively splits, then merges into existing root. Even no eligible faces produces an empty node with origin bounds and still calls merge. Does not itself load Room60; caller supplies that root.
// UNREALRED VERIFIED [combat-native-query-20261104]: Incremental insertion gathers only spatially-unowned faces and rejects flag4 liquid, builds a separate subtree in room-list order, then557750 merges it. This differs from557450 initial all-face seeding. A full rebuild can change native first-hit/tree ordering after mutation.
float *__thiscall rf_room_spatial_tree_insert_unowned_faces(void *this, void *a2)
{
  int i; // [esp+4h] [ebp-8h]
  int *v5; // [esp+8h] [ebp-4h]

  v5 = (int *)rf_geomod_spatial_node_allocate();
  for ( i = rf_receiver_get_first_dword(a2); i; i = rf_face_next_room_link(i) )
  {
    if ( !*(_DWORD *)(i + 72) && !rf_face_is_liquid((_DWORD *)(i + 40)) )
    {
      rf_geomod_spatial_node_face_list_append(v5 + 6, i);
      *(_DWORD *)(i + 72) = v5;
    }
  }
  rf_geomod_spatial_node_finalize_bounds((float *)v5);
  rf_geomod_spatial_tree_build_recursive((char *)v5, 0);
  return rf_spatial_tree_merge((int)this, (float *)v5);
}

