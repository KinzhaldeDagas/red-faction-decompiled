// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557450 rf_spatial_tree_build_from_face_list
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): ECX root plus caller intrusive room-face list. Clears root face-list head/tail24/28 without unlinking prior owners, traverses input through Face92, appends each to root spatial list and sets Face72=root. Finalizes bounds then recursively splits with depth0; returns0. Does not release existing children or guard repeated builds on populated tree.
// UNREALRED VERIFIED [combat-native-query-20261104]: Initial tree seeding appends EVERY supplied room face with reciprocal Face+72 node owner, without a liquid/unknown/invisible filter. Finalize bounds then557050. Initial world trees are built before477370 liquid generation; newly generated liquids attach to room lists without becoming initial tree faces. Do not rebuild an ordinary tree from all post-liquid faces.
int __thiscall rf_spatial_tree_build_from_face_list(int this, void *a2)
{
  int i; // [esp+4h] [ebp-4h]

  rf_intrusive_list_reset_head_tail((_DWORD *)(this + 24));
  for ( i = rf_receiver_get_first_dword(a2); i; i = rf_face_next_room_link(i) )
  {
    rf_geomod_spatial_node_face_list_append((int *)(this + 24), i);
    *(_DWORD *)(i + 72) = this;
  }
  rf_geomod_spatial_node_finalize_bounds((float *)this);
  rf_geomod_spatial_tree_build_recursive((char *)this, 0);
  return 0;
}

