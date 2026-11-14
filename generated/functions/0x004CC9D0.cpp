// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CC9D0 sub_4CC9D0
// UNREALRED VERIFIED [particle-contact-geometry-20261104] Particle finite-segment trace over one ordered spatial tree. For overlapping nodes, scans node face list +24 via 0x4CA800 before traversing children. Each face must overlap segment bounds, pass one-sided plane test 0x569600 with strict t < 1, and contain the projected hit via 0x5337E0. First admitted face returns hit point, normal, local segment fraction and face pointer; this is not closest-hit selection. Pushes child +32 then +36 on a LIFO stack, so +36 is visited first. No additional face-flag predicate is applied in this body.
char __cdecl sub_4CC9D0(int a1, float *a2, float *a3, float *lhs, int a5)
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

  unk_866800[0] = a1;
  v14 = 1;
  while ( v14 > 0 )
  {
    unk_8667F8 = unk_866800[--v14];
    if ( rf_aabb_overlap_strict_ordered(unk_8667F8, (float *)(unk_8667F8 + 12), a2, a3) )
    {
      for ( source = (float *)rf_receiver_get_first_dword((void *)(unk_8667F8 + 24));
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
      if ( *(_DWORD *)(unk_8667F8 + 32) )
        unk_866800[v14++] = *(_DWORD *)(unk_8667F8 + 32);
      if ( *(_DWORD *)(unk_8667F8 + 36) )
        unk_866800[v14++] = *(_DWORD *)(unk_8667F8 + 36);
    }
  }
  return 0;
}

