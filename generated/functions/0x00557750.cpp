// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557750 rf_spatial_tree_merge
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): ECX existing root plus incoming root. If existing has BOTH children and incoming bounds strictly inside existing bounds, computes incoming center and descends child32 only when center is strictly greater than child32 MINIMUM on ALL axes via556F10, otherwise child36; does not test that child fully contains incoming. Otherwise allocates40-byte copy node containing old root bounds/children, moves all old root faces to it and reparents Face72, expands existing root bounds by incoming bounds, increments global15A7158, and replaces existing children with(copyNode,incoming). Existing root identity stays stable. No null/alias/cycle/allocation checks; incoming root pointer returned from graft branch.
float *__thiscall rf_spatial_tree_merge(int this, float *lhs)
{
  float *v3; // eax
  float sum_result[3]; // [esp+8h] [ebp-3Ch] BYREF
  float v6[3]; // [esp+14h] [ebp-30h] BYREF
  float copy_result[3]; // [esp+20h] [ebp-24h] BYREF
  float scaled_result[3]; // [esp+2Ch] [ebp-18h] BYREF
  int spatial_node_link; // [esp+38h] [ebp-Ch]
  float *destination; // [esp+3Ch] [ebp-8h]
  int i; // [esp+40h] [ebp-4h]

  if ( *(_DWORD *)(this + 32)
    && *(_DWORD *)(this + 36)
    && rf_aabb_strictly_inside_bounds(lhs, (float *)this, (float *)(this + 12)) )
  {
    v3 = rf_vector_add(lhs, sum_result, lhs + 3);
    rf_vector_multiply_scalar(v3, scaled_result, 0.5);
    if ( rf_vector3_all_components_strictly_greater(scaled_result, *(float **)(this + 32)) )
      return (float *)rf_spatial_tree_merge(*(_DWORD *)(this + 32), (int)lhs);
    else
      return (float *)rf_spatial_tree_merge(*(_DWORD *)(this + 36), (int)lhs);
  }
  else
  {
    destination = (float *)rf_geomod_spatial_node_allocate();
    rf_vector_copy(destination, copy_result, (const float *)this);
    rf_vector_copy(destination + 3, v6, (const float *)(this + 12));
    destination[8] = *(float *)(this + 32);
    destination[9] = *(float *)(this + 36);
    for ( i = rf_receiver_get_first_dword((void *)(this + 24)); i; i = spatial_node_link )
    {
      spatial_node_link = rf_face_next_spatial_node_link(i);
      rf_geomod_spatial_node_face_list_remove((int *)(this + 24), i);
      rf_geomod_spatial_node_face_list_append((int *)destination + 6, i);
      *(_DWORD *)(i + 72) = destination;
    }
    rf_aabb_union_componentwise_in_place((float *)this, (float *)(this + 12), lhs, lhs + 3);
    ++unk_15A7158;
    *(_DWORD *)(this + 32) = destination;
    *(_DWORD *)(this + 36) = lhs;
    return lhs;
  }
}

