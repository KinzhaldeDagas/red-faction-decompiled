// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C6B70 rf_glass_find_first_spatial_tree_segment_hit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl(root,segmentMin,segmentMax,startDeltaPair,result40). Global LIFO stack8367D8 and current-node8367D0; seeds root evenNULL, no root validation/bounds guard. Pop nodes while
// signed stackCount>0; strict ordered node AABB0/12 overlap. Visits node face list24 FIRST, next_spatial_node_link order; face AABB16/28 overlap, front-plane helper,STRICT ORDERED
// t<1, candidate point written before polygon containment. FIRST contained candidate writes normal20,fraction4,face36 and returnsAL1, not nearest hit. Does not read incoming
// fraction/count or increment result.count0; false may leave candidate point modified.
// If no contained face, pushes child32 then child36, so LIFO visits child36 before32. No global face-cache participation, near/far sorting, stack capacity/cycle guard,
// thread/reentrancy isolation or portal/liquid filtering here. Traversal order matters within tree; callback contains/projection routines do not turn this into closest-hit selection.
char __cdecl rf_glass_find_first_spatial_tree_segment_hit(int a1, float *a2, float *a3, float *lhs, int a5)
{
  float *v5; // eax
  float *v6; // eax
  float v8[3]; // [esp+4h] [ebp-3Ch] BYREF
  float copy_result[3]; // [esp+10h] [ebp-30h] BYREF
  float sum_result[3]; // [esp+1Ch] [ebp-24h] BYREF
  float scaled_result[3]; // [esp+28h] [ebp-18h] BYREF
  float *source; // [esp+34h] [ebp-Ch]
  float scalar; // [esp+38h] [ebp-8h] BYREF
  int v14; // [esp+3Ch] [ebp-4h]

  unk_8367D8[0] = a1;
  v14 = 1;
  while ( v14 > 0 )
  {
    unk_8367D0 = unk_8367D8[--v14];
    if ( rf_aabb_overlap_strict_ordered(unk_8367D0, (float *)(unk_8367D0 + 12), a2, a3) )
    {
      for ( source = (float *)rf_receiver_get_first_dword((void *)(unk_8367D0 + 24));
            source;
            source = (float *)rf_face_next_spatial_node_link((int)source) )
      {
        if ( rf_aabb_overlap_strict_ordered(source + 4, source + 7, a2, a3) )
        {
          if ( rf_polygon_segment_intersect_front_plane(lhs, lhs + 3, source, &scalar) )
          {
            if ( scalar < 1.0 )
            {
              v5 = rf_vector_multiply_scalar(lhs + 3, scaled_result, scalar);
              v6 = rf_vector_add(lhs, sum_result, v5);
              rf_vector_copy((float *)(a5 + 8), copy_result, v6);
              if ( rf_geomod_face_contains_projected_point(source, a5 + 8) )
              {
                rf_vector_copy((float *)(a5 + 20), v8, source);
                *(float *)(a5 + 4) = scalar;
                *(_DWORD *)(a5 + 36) = source;
                return 1;
              }
            }
          }
        }
      }
      if ( *(_DWORD *)(unk_8367D0 + 32) )
        unk_8367D8[v14++] = *(_DWORD *)(unk_8367D0 + 32);
      if ( *(_DWORD *)(unk_8367D0 + 36) )
        unk_8367D8[v14++] = *(_DWORD *)(unk_8367D0 + 36);
    }
  }
  return 0;
}

