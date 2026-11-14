// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557050 rf_geomod_spatial_tree_build_recursive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Splits node AABB at midpoint of longest extent: strict comparisons keep X on ties, then Y ahead of Z on remaining ties. Counts faces inclusively fitting high half first, then low; straddlers stay in parent. Allocates BOTH children only if both counts nonzero, moves matching faces preserving traversal order and updates Face72 owner. Computes child bounds and recurses high child32 then low36. Depth argument only increments; no depth/size limit uses it. Existing children are overwritten on split without disposal; allocator failures unchecked. Parent bounds retain original aggregate; no split when one side empty even if many movable faces.
int __thiscall rf_geomod_spatial_tree_build_recursive(char *this, int a2)
{
  int result; // eax
  int spatial_node_link; // [esp+8h] [ebp-58h]
  float v5; // [esp+Ch] [ebp-54h] BYREF
  float v6; // [esp+10h] [ebp-50h]
  float v7; // [esp+14h] [ebp-4Ch]
  float v8; // [esp+18h] [ebp-48h] BYREF
  float v9; // [esp+1Ch] [ebp-44h]
  float v10; // [esp+20h] [ebp-40h]
  int v11; // [esp+24h] [ebp-3Ch]
  float v12; // [esp+28h] [ebp-38h] BYREF
  float v13; // [esp+2Ch] [ebp-34h]
  float v14; // [esp+30h] [ebp-30h]
  float v15; // [esp+34h] [ebp-2Ch] BYREF
  float v16; // [esp+38h] [ebp-28h]
  float v17; // [esp+3Ch] [ebp-24h]
  int v18; // [esp+40h] [ebp-20h]
  int v19; // [esp+44h] [ebp-1Ch]
  int i; // [esp+48h] [ebp-18h]
  float v21; // [esp+4Ch] [ebp-14h]
  int v22; // [esp+50h] [ebp-10h]
  float v23; // [esp+54h] [ebp-Ch] BYREF
  float v24; // [esp+58h] [ebp-8h]
  float v25; // [esp+5Ch] [ebp-4h]

  rf_vector3_default_construct_noop(&v23);
  v23 = (*((float *)this + 3) + *(float *)this) / 2.0;
  v24 = (*((float *)this + 4) + *((float *)this + 1)) / 2.0;
  v25 = (*((float *)this + 5) + *((float *)this + 2)) / 2.0;
  v21 = *((float *)this + 3) - *(float *)this;
  v22 = 0;
  if ( v21 < *((float *)this + 4) - *((float *)this + 1) )
  {
    v21 = *((float *)this + 4) - *((float *)this + 1);
    v22 = 1;
  }
  if ( v21 < *((float *)this + 5) - *((float *)this + 2) )
  {
    v21 = *((float *)this + 5) - *((float *)this + 2);
    v22 = 2;
  }
  rf_vector3_default_construct_noop(&v8);
  rf_vector3_default_construct_noop(&v5);
  rf_vector3_default_construct_noop(&v12);
  rf_vector3_default_construct_noop(&v15);
  if ( v22 )
  {
    if ( v22 == 1 )
    {
      v8 = *(float *)this;
      v9 = v24;
      v10 = *((float *)this + 2);
      v5 = *((float *)this + 3);
      v6 = *((float *)this + 4);
      v7 = *((float *)this + 5);
      v12 = *(float *)this;
      v13 = *((float *)this + 1);
      v14 = *((float *)this + 2);
      v15 = *((float *)this + 3);
      v16 = v24;
      v17 = *((float *)this + 5);
    }
    else if ( v22 == 2 )
    {
      v8 = *(float *)this;
      v9 = *((float *)this + 1);
      v10 = v25;
      v5 = *((float *)this + 3);
      v6 = *((float *)this + 4);
      v7 = *((float *)this + 5);
      v12 = *(float *)this;
      v13 = *((float *)this + 1);
      v14 = *((float *)this + 2);
      v15 = *((float *)this + 3);
      v16 = *((float *)this + 4);
      v17 = v25;
    }
  }
  else
  {
    v8 = v23;
    v9 = *((float *)this + 1);
    v10 = *((float *)this + 2);
    v5 = *((float *)this + 3);
    v6 = *((float *)this + 4);
    v7 = *((float *)this + 5);
    v12 = *(float *)this;
    v13 = *((float *)this + 1);
    v14 = *((float *)this + 2);
    v15 = v23;
    v16 = *((float *)this + 4);
    v17 = *((float *)this + 5);
  }
  v18 = 0;
  v19 = 0;
  v11 = 0;
  result = rf_receiver_get_first_dword(this + 24);
  for ( i = result; i; i = result )
  {
    if ( rf_face_aabb_inside_bounds_inclusive(i, &v8, &v5) )
    {
      ++v19;
    }
    else if ( rf_face_aabb_inside_bounds_inclusive(i, &v12, &v15) )
    {
      ++v11;
    }
    else
    {
      ++v18;
    }
    result = rf_face_next_spatial_node_link(i);
  }
  if ( v19 && v11 )
  {
    *((_DWORD *)this + 8) = rf_geomod_spatial_node_allocate();
    *((_DWORD *)this + 9) = rf_geomod_spatial_node_allocate();
    for ( i = rf_receiver_get_first_dword(this + 24); i; i = spatial_node_link )
    {
      spatial_node_link = rf_face_next_spatial_node_link(i);
      if ( rf_face_aabb_inside_bounds_inclusive(i, &v8, &v5) )
      {
        rf_geomod_spatial_node_face_list_remove((int *)this + 6, i);
        rf_geomod_spatial_node_face_list_append((int *)(*((_DWORD *)this + 8) + 24), i);
        *(_DWORD *)(i + 72) = *((_DWORD *)this + 8);
      }
      else if ( rf_face_aabb_inside_bounds_inclusive(i, &v12, &v15) )
      {
        rf_geomod_spatial_node_face_list_remove((int *)this + 6, i);
        rf_geomod_spatial_node_face_list_append((int *)(*((_DWORD *)this + 9) + 24), i);
        *(_DWORD *)(i + 72) = *((_DWORD *)this + 9);
      }
    }
    rf_geomod_spatial_node_finalize_bounds(*((float **)this + 8));
    rf_geomod_spatial_tree_build_recursive(*((char **)this + 8), a2 + 1);
    rf_geomod_spatial_node_finalize_bounds(*((float **)this + 9));
    return rf_geomod_spatial_tree_build_recursive(*((char **)this + 9), a2 + 1);
  }
  return result;
}

