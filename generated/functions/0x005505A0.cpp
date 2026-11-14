// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005505A0 rf_lightmap_build_shadow_mask_by_face_rays
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Arguments solidcontext,lightmaprecord,lightrecord,unused,maskbytes. Computes lightmapinteriorUV center and worldpoint via0x54D700,initializes width*height maskbytes to1. Only raytests when dot(lightposition+12-center,recordnormal+108)>0. Expands localAABB record+52/+64 toinclude light. Loops BOTH rows andcolumns against recordwidth+24 (assemblyconfirmed),not height+28; nonsquare lightmaps therefore leave rowsuntouched orwrite beyond initializedwidth*heightmask. Perpixel uses atlasUV at integercoordinates(no+0.5),dispatches worldmapping,rayvector=lightposition-worldpoint. Walks solidfaces,excluding same lightmapindex+54,portal,liquid,and failedAABBoverlap. A front-plane segmenthit plus polygoncontainment setsmaskbyte0; otherwise retains1. No lightdistance/samplecount/widthheightagreement guard. Does not honor receiver-space
// transformedlightposition here; uses light+12.
void __cdecl rf_lightmap_build_shadow_mask_by_face_rays(int a1, int a2, int a3, int a4, char *a5)
{
  float *v5; // eax
  float v6; // [esp+10h] [ebp-C8h]
  float v7; // [esp+14h] [ebp-C4h]
  float scaled_result[3]; // [esp+28h] [ebp-B0h] BYREF
  float v9[3]; // [esp+34h] [ebp-A4h] BYREF
  float copy_result[3]; // [esp+40h] [ebp-98h] BYREF
  float sum_result[3]; // [esp+4Ch] [ebp-8Ch] BYREF
  float lhs[3]; // [esp+58h] [ebp-80h] BYREF
  float v13; // [esp+64h] [ebp-74h]
  float *k; // [esp+68h] [ebp-70h]
  float scalar; // [esp+6Ch] [ebp-6Ch] BYREF
  int v16; // [esp+70h] [ebp-68h]
  float vector[3]; // [esp+74h] [ebp-64h] BYREF
  float v18; // [esp+80h] [ebp-58h]
  int v19; // [esp+84h] [ebp-54h]
  float v20; // [esp+88h] [ebp-50h]
  float v21; // [esp+8Ch] [ebp-4Ch]
  float v22; // [esp+90h] [ebp-48h]
  float out_vector[3]; // [esp+94h] [ebp-44h] BYREF
  float v24; // [esp+A0h] [ebp-38h]
  float v25; // [esp+A4h] [ebp-34h]
  float v26[3]; // [esp+A8h] [ebp-30h] BYREF
  float v27; // [esp+B4h] [ebp-24h]
  float destination[3]; // [esp+B8h] [ebp-20h] BYREF
  int j; // [esp+C4h] [ebp-14h]
  int i; // [esp+C8h] [ebp-10h]
  float rhs[3]; // [esp+CCh] [ebp-Ch] BYREF

  v24 = 1.0 / (double)*(int *)(*(_DWORD *)(a2 + 12) + 4);
  v21 = 1.0 / (double)*(int *)(*(_DWORD *)(a2 + 12) + 8);
  v20 = (double)(*(_DWORD *)(a2 + 16) + 1) * v24;
  v27 = (double)(*(_DWORD *)(a2 + 20) + 1) * v21;
  v25 = (double)(*(_DWORD *)(a2 + 24) - 2) * v24 + v20;
  v22 = (double)(*(_DWORD *)(a2 + 28) - 2) * v21 + v27;
  rf_vector3_default_construct_noop(rhs);
  v7 = (v22 - v27) * 0.5 + v27;
  v6 = (v25 - v20) * 0.5 + v20;
  rf_lightmap_uv_to_world_dispatch(a2, v6, v7, (int)rhs);
  memset(a5, 1, *(_DWORD *)(a2 + 28) * *(_DWORD *)(a2 + 24));
  rf_vector_subtract((const float *)(a3 + 12), out_vector, rhs);
  if ( rf_vector_dot(out_vector, (float *)(a2 + 108)) > 0.0 )
  {
    rf_vector3_default_construct_noop(destination);
    rf_vector3_default_construct_noop(v26);
    rf_vector_copy(destination, copy_result, (const float *)(a2 + 52));
    rf_vector_copy(v26, v9, (const float *)(a2 + 64));
    rf_aabb_include_point_min_else_max(destination, v26, (float *)(a3 + 12));
    for ( i = 0; i < *(_DWORD *)(a2 + 24); ++i )
    {
      v19 = *(_DWORD *)(a2 + 20) + i;
      v18 = (double)v19 * v21;
      v18 = v18 - *(float *)(a2 + 88);
      v18 = v18 / *(float *)(a2 + 80);
      for ( j = 0; j < *(_DWORD *)(a2 + 24); ++j )
      {
        v16 = *(_DWORD *)(a2 + 16) + j;
        v13 = (double)v16 * v24;
        v13 = v13 - *(float *)(a2 + 84);
        v13 = v13 / *(float *)(a2 + 76);
        rf_vector3_default_construct_noop(lhs);
        ((void (__thiscall *)(int, _DWORD, _DWORD, float *))unk_1425E98[4 * *(_DWORD *)(a2 + 92)])(
          unk_1425E9C[4 * *(_DWORD *)(a2 + 92)] + a2,
          LODWORD(v13),
          LODWORD(v18),
          lhs);
        rf_vector_subtract((const float *)(a3 + 12), vector, lhs);
        for ( k = (float *)rf_receiver_get_first_dword((void *)(a1 + 112)); k; k = (float *)rf_solid_face_next_link((int)k) )
        {
          if ( *((__int16 *)k + 27) != *(_DWORD *)a2
            && !rf_face_is_portal((__int16 *)k + 20)
            && !rf_face_is_liquid((_DWORD *)k + 10)
            && rf_aabb_overlap_strict_ordered(destination, v26, k + 4, k + 7) )
          {
            if ( rf_polygon_segment_intersect_front_plane(lhs, vector, k, &scalar) )
            {
              v5 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
              rf_vector_add(lhs, sum_result, v5);
              if ( rf_geomod_face_contains_projected_point(k, (char *)sum_result) )
              {
                *a5 = 0;
                break;
              }
            }
          }
        }
        ++a5;
      }
    }
  }
}

