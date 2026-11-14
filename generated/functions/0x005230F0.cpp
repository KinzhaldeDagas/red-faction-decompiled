// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005230F0 rf_world_decal_clip_and_attach_face_polygon
// UNREALRED VERIFIED [decal-projection-20261028]: Rejects portal,liquid,flag test0x525B20,invisible,or authored-sky-owner faces; also requires face AABB overlap,decal-box-vs-face-plane helper0x5B1960,and dot(decal row+36,face normal)<=-0.25. If byte argument nonzero scans existing face polygon chain+76 and rejects same decal owner+1316. Copies authored face loop positions into local25-vec3 buffer with no capacity check; clips successively against six planes at decal+92+16*i using rf_clip_polygon_against_plane, alternating two25-entry buffers; any resulting count<3 exits. Requires global polygon count0xCFACA0<2000, then acquires1332-byte polygon without null-result check. Normal branch stores clipped positions at polygon+228+44*i and base UV+212/+216 from NEGATED signed distances to planes+172/+92 divided by dimensions x/y, clamped0..1; vertex count+208. Lightmap texture+204/UV+220/+224
// derive from face index+54 in alternate context+232 ifpresent, otherwise main context+72, or handle-1 for absent lightmap. Flag8 branch instead computes temporary UVs from ORIGINAL face vertices, uses flags0x40/0x80 and scalar+88 for aspect scaling, then0x523A80. Both branches set polygon face-owner+1312,decal-owner+1316, append circular per-decal links+1320/+1324, increment decal polygon count+216. OR face flags+40 with0x200000 for flag8,else0x100000; may add decal to room-owner array+156 through0x525B90, then links polygon to face via0x535A30. No zero-dimension guard or bitmap allocation; no status return.
void __cdecl rf_world_decal_clip_and_attach_face_polygon(int a1, int a2, char a3)
{
  double v3; // st7
  double v4; // st7
  float *v5; // eax
  float *v6; // eax
  double v7; // st7
  double v8; // st7
  int v9; // ecx
  float v10; // [esp+4h] [ebp-2E4h]
  float v11; // [esp+4h] [ebp-2E4h]
  int v12; // [esp+8h] [ebp-2E0h]
  int v13; // [esp+Ch] [ebp-2DCh]
  float *destination; // [esp+10h] [ebp-2D8h]
  float v15[3]; // [esp+14h] [ebp-2D4h] BYREF
  float copy_result[3]; // [esp+20h] [ebp-2C8h] BYREF
  float v17; // [esp+2Ch] [ebp-2BCh]
  float v18; // [esp+30h] [ebp-2B8h]
  float v19; // [esp+34h] [ebp-2B4h]
  float v20; // [esp+38h] [ebp-2B0h]
  int m; // [esp+3Ch] [ebp-2ACh]
  float v22; // [esp+40h] [ebp-2A8h] BYREF
  float v23; // [esp+44h] [ebp-2A4h]
  int v24; // [esp+48h] [ebp-2A0h]
  int v25; // [esp+4Ch] [ebp-29Ch]
  float v26; // [esp+50h] [ebp-298h] BYREF
  float v27; // [esp+54h] [ebp-294h]
  int v28; // [esp+58h] [ebp-290h]
  int v29; // [esp+5Ch] [ebp-28Ch]
  int v30; // [esp+60h] [ebp-288h]
  int v31; // [esp+64h] [ebp-284h]
  int v32; // [esp+68h] [ebp-280h]
  int i; // [esp+6Ch] [ebp-27Ch]
  int j; // [esp+70h] [ebp-278h]
  int v35; // [esp+74h] [ebp-274h]
  char v36[304]; // [esp+78h] [ebp-270h] BYREF
  char v37[304]; // [esp+1A8h] [ebp-140h] BYREF
  char *v38; // [esp+2D8h] [ebp-10h]
  _DWORD *v39; // [esp+2DCh] [ebp-Ch]
  int k; // [esp+2E0h] [ebp-8h]
  char *v41; // [esp+2E4h] [ebp-4h]

  if ( !rf_face_is_portal((__int16 *)(a2 + 40))
    && !rf_face_is_liquid((_DWORD *)(a2 + 40))
    && !rf_face_flags_test_bit80((_DWORD *)(a2 + 40))
    && !rf_face_is_invisible((_DWORD *)(a2 + 40))
    && (!*(_DWORD *)(a2 + 68) || !rf_room_is_authored_sky(*(_BYTE **)(a2 + 68)))
    && rf_aabb_overlap_inclusive((float *)(a2 + 16), (float *)(a2 + 28), (float *)(a1 + 188), (float *)(a1 + 200))
    && rf_plane_intersects_aabb_closed((float *)(a1 + 188), (float *)(a1 + 200), (float *)a2)
    && rf_vector_dot((float *)(a1 + 36), (float *)a2) <= -0.25 )
  {
    if ( a3 )
    {
      for ( i = *(_DWORD *)(a2 + 76); i; i = *(_DWORD *)(i + 1328) )
      {
        if ( *(_DWORD *)(i + 1316) == a1 )
          return;
      }
    }
    rf_vector_construct_no_unwind(v37, 0xCu, 25, rf_vector3_default_construct_noop);
    rf_vector_construct_no_unwind(v36, 0xCu, 25, rf_vector3_default_construct_noop);
    v35 = 0;
    for ( j = *(_DWORD *)(a2 + 64); j; j = v13 )
    {
      destination = (float *)&v37[12 * v35++];
      rf_vector_copy(destination, copy_result, *(const float **)j);
      if ( *(_DWORD *)(j + 20) == *(_DWORD *)(a2 + 64) )
        v13 = 0;
      else
        v13 = *(_DWORD *)(j + 20);
    }
    v38 = v37;
    v41 = v36;
    for ( k = 0; k < 6; ++k )
    {
      v32 = rf_clip_polygon_against_plane(v35, (int)v38, (int)v41, a1 + 16 * k + 92);
      if ( v32 < 3 )
      {
        v35 = 0;
        return;
      }
      v35 = v32;
      v31 = (int)v38;
      v38 = v41;
      v41 = (char *)v31;
    }
    if ( unk_CFACA0 < 2000 )
    {
      v39 = rf_decal_polygon_pool_acquire(dword_A70648);
      if ( (*(_DWORD *)(a1 + 80) & 8) != 0 )
      {
        if ( (*(_DWORD *)(a1 + 80) & 0x40) != 0 )
        {
          v19 = 1.0;
          v18 = *(float *)(a1 + 48) / *(float *)(a1 + 52);
          v20 = v18 * *(float *)(a1 + 88);
        }
        else if ( (*(_DWORD *)(a1 + 80) & 0x80) != 0 )
        {
          v20 = 1.0;
          v17 = *(float *)(a1 + 52) / *(float *)(a1 + 48);
          v19 = v17 * *(float *)(a1 + 88);
        }
        else
        {
          v20 = 1.0;
          v19 = 1.0;
        }
        k = 0;
        for ( m = *(_DWORD *)(a2 + 64); m; m = v12 )
        {
          v7 = rf_plane_point_signed_distance((float *)(a1 + 172), (float *)*(_DWORD *)m);
          *(float *)&v39[2 * k] = -v7 / *(float *)(a1 + 48) * v20;
          v8 = rf_plane_point_signed_distance((float *)(a1 + 92), (float *)*(_DWORD *)m);
          *(float *)&v39[2 * k++ + 1] = -v8 / *(float *)(a1 + 52) * v19;
          if ( *(_DWORD *)(m + 20) == *(_DWORD *)(a2 + 64) )
            v12 = 0;
          else
            v12 = *(_DWORD *)(m + 20);
        }
        rf_decal_uv_shift_selected_axis_to_minimum_tile((int)v39, k, *(_DWORD *)(a1 + 80) & 0xC0);
      }
      else
      {
        for ( k = 0; k < v35; ++k )
        {
          v30 = (int)&v39[11 * k + 53];
          rf_vector_copy((float *)&v39[11 * k + 57], v15, (const float *)&v38[12 * k]);
          v3 = rf_plane_point_signed_distance((float *)(a1 + 172), (float *)&v38[12 * k]);
          *(float *)v30 = -v3 / *(float *)(a1 + 48);
          rf_float_clamp_in_place((float *)v30, 0.0, 1.0);
          v4 = rf_plane_point_signed_distance((float *)(a1 + 92), (float *)&v38[12 * k]);
          *(float *)(v30 + 4) = -v4 / *(float *)(a1 + 52);
          rf_float_clamp_in_place((float *)(v30 + 4), 0.0, 1.0);
        }
        v39[52] = v35;
        if ( *(_DWORD *)(a1 + 232) )
        {
          if ( *(__int16 *)(a2 + 54) < 0 )
          {
            v39[51] = -1;
          }
          else
          {
            v24 = *(_DWORD *)sub_552200((_DWORD *)(*(_DWORD *)(a1 + 232) + 192), *(__int16 *)(a2 + 54));
            v25 = *(_DWORD *)(v24 + 12);
            v39[51] = *(_DWORD *)(v25 + 16);
            for ( k = 0; k < v35; ++k )
            {
              v11 = *(float *)rf_vector_component_address_unchecked((char *)&v39[11 * k + 57], *(_DWORD *)(v24 + 100));
              v6 = (float *)rf_vector_component_address_unchecked((char *)&v39[11 * k + 57], *(_DWORD *)(v24 + 96));
              rf_vector2_assign_components(&v22, *v6, v11);
              v22 = v22 * *(float *)(v24 + 76);
              v23 = v23 * *(float *)(v24 + 80);
              rf_vector2_accumulate(&v22, (float *)(v24 + 84));
              *(float *)&v39[11 * k + 55] = v22;
              *(float *)&v39[11 * k + 56] = v23;
              rf_float_clamp_in_place((float *)&v39[11 * k + 55], 0.0, 1.0);
              rf_float_clamp_in_place((float *)&v39[11 * k + 56], 0.0, 1.0);
            }
          }
        }
        else if ( *(__int16 *)(a2 + 54) < 0 )
        {
          v39[51] = -1;
        }
        else
        {
          v28 = *(_DWORD *)sub_552200((_DWORD *)(*(_DWORD *)(a1 + 72) + 192), *(__int16 *)(a2 + 54));
          v29 = *(_DWORD *)(v28 + 12);
          v39[51] = *(_DWORD *)(v29 + 16);
          for ( k = 0; k < v35; ++k )
          {
            v10 = *(float *)rf_vector_component_address_unchecked((char *)&v39[11 * k + 57], *(_DWORD *)(v28 + 100));
            v5 = (float *)rf_vector_component_address_unchecked((char *)&v39[11 * k + 57], *(_DWORD *)(v28 + 96));
            rf_vector2_assign_components(&v26, *v5, v10);
            v26 = v26 * *(float *)(v28 + 76);
            v27 = v27 * *(float *)(v28 + 80);
            rf_vector2_accumulate(&v26, (float *)(v28 + 84));
            *(float *)&v39[11 * k + 55] = v26;
            *(float *)&v39[11 * k + 56] = v27;
            rf_float_clamp_in_place((float *)&v39[11 * k + 55], 0.0, 1.0);
            rf_float_clamp_in_place((float *)&v39[11 * k + 56], 0.0, 1.0);
          }
        }
      }
      v39[329] = a1;
      v39[328] = a2;
      if ( *(_DWORD *)(a1 + 212) )
      {
        v39[331] = *(_DWORD *)(*(_DWORD *)(a1 + 212) + 1324);
        v39[330] = *(_DWORD *)(a1 + 212);
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 212) + 1324) + 1320) = v39;
        *(_DWORD *)(*(_DWORD *)(a1 + 212) + 1324) = v39;
      }
      else
      {
        v39[330] = v39;
        v39[331] = v39;
        *(_DWORD *)(a1 + 212) = v39;
      }
      ++*(_DWORD *)(a1 + 216);
      if ( (*(_DWORD *)(a1 + 80) & 8) != 0 )
        v9 = *(_DWORD *)(a2 + 40) | 0x200000;
      else
        v9 = *(_DWORD *)(a2 + 40) | 0x100000;
      *(_DWORD *)(a2 + 40) = v9;
      if ( *(_DWORD *)(a2 + 68) && unknown_libname_11(*(void **)(a2 + 68)) )
        rf_inline_pointer_array_append_unique_capacity48((_DWORD *)(*(_DWORD *)(a2 + 68) + 156), a1);
      rf_face_prepend_decal_polygon_link((_DWORD *)a2, (int)v39);
    }
  }
}

