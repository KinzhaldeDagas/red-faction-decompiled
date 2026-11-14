// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052D560 rf_geomod_boolean_stage_5_policy_rooms
// UNREALRED VERIFIED [combat-native-followup-20261104]: Affected room collection follows ordered workspace WORLD-operand faces whose selected action is Delete, deduplicating by first room encounter. After geometry/tree publication, detail registry scan preserves existing refs and appends new candidates only. Native policy includes inclusive room/face AABB overlap plus first-detail-face/first-corner point-room fallback. No reference pruning is present in this tail. Final snapped triangle snapshots do not retain native workspace order/classification, so recomputing only from final geometry is not equivalent.
_DWORD *__cdecl rf_geomod_boolean_stage_5_policy_rooms(float *a1, int a2)
{
  _DWORD *v2; // esi
  _DWORD *v3; // esi
  unsigned int v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  _DWORD *result; // eax
  int first_dword; // eax
  float v11; // [esp+0h] [ebp-1A0h]
  float v12; // [esp+0h] [ebp-1A0h]
  float v13; // [esp+0h] [ebp-1A0h]
  float v14; // [esp+0h] [ebp-1A0h]
  float v15; // [esp+4h] [ebp-19Ch]
  float v16; // [esp+4h] [ebp-19Ch]
  float v17; // [esp+4h] [ebp-19Ch]
  float v18; // [esp+4h] [ebp-19Ch]
  int v19; // [esp+14h] [ebp-18Ch]
  void *v20; // [esp+18h] [ebp-188h]
  float v21[3]; // [esp+1Ch] [ebp-184h] BYREF
  int v22; // [esp+28h] [ebp-178h]
  int ii; // [esp+2Ch] [ebp-174h]
  float *v24; // [esp+30h] [ebp-170h]
  int jj; // [esp+34h] [ebp-16Ch]
  char v26; // [esp+3Bh] [ebp-165h]
  int n; // [esp+3Ch] [ebp-164h]
  int v28; // [esp+40h] [ebp-160h]
  int v29; // [esp+44h] [ebp-15Ch]
  int v30; // [esp+48h] [ebp-158h]
  int v31; // [esp+4Ch] [ebp-154h]
  int v32; // [esp+50h] [ebp-150h]
  _DWORD *v33; // [esp+54h] [ebp-14Ch]
  char v34; // [esp+5Bh] [ebp-145h]
  int v35; // [esp+5Ch] [ebp-144h]
  float v36[3]; // [esp+60h] [ebp-140h] BYREF
  float v37; // [esp+6Ch] [ebp-134h]
  float v38; // [esp+70h] [ebp-130h]
  float v39[3]; // [esp+74h] [ebp-12Ch] BYREF
  float v40[2]; // [esp+80h] [ebp-120h] BYREF
  float v41; // [esp+88h] [ebp-118h]
  float v42[3]; // [esp+8Ch] [ebp-114h] BYREF
  int v43; // [esp+98h] [ebp-108h] BYREF
  float v44[3]; // [esp+9Ch] [ebp-104h] BYREF
  float v45; // [esp+A8h] [ebp-F8h]
  float *v46; // [esp+ACh] [ebp-F4h]
  float v47[2]; // [esp+B0h] [ebp-F0h] BYREF
  float v48; // [esp+B8h] [ebp-E8h]
  int v49; // [esp+BCh] [ebp-E4h] BYREF
  float v50; // [esp+C0h] [ebp-E0h]
  float v51[3]; // [esp+C4h] [ebp-DCh] BYREF
  unsigned int v52[2]; // [esp+D0h] [ebp-D0h] BYREF
  int generated_handle_unchecked; // [esp+D8h] [ebp-C8h]
  float v54[3]; // [esp+E8h] [ebp-B8h] BYREF
  float v55[3]; // [esp+F4h] [ebp-ACh] BYREF
  char v56[48]; // [esp+100h] [ebp-A0h] BYREF
  char v57[12]; // [esp+130h] [ebp-70h] BYREF
  float v58; // [esp+13Ch] [ebp-64h]
  float v59[9]; // [esp+140h] [ebp-60h] BYREF
  float v60; // [esp+164h] [ebp-3Ch]
  float v61; // [esp+168h] [ebp-38h]
  float v62; // [esp+16Ch] [ebp-34h]
  float v63; // [esp+170h] [ebp-30h]
  int v64; // [esp+174h] [ebp-2Ch]
  _DWORD *v65; // [esp+178h] [ebp-28h]
  _DWORD *v66; // [esp+17Ch] [ebp-24h]
  int link; // [esp+180h] [ebp-20h]
  float *j; // [esp+184h] [ebp-1Ch]
  int v69; // [esp+188h] [ebp-18h]
  int i; // [esp+18Ch] [ebp-14h]
  int k; // [esp+194h] [ebp-Ch]
  char v73; // [esp+19Bh] [ebp-5h]
  int m; // [esp+19Ch] [ebp-4h]

  v73 = 0;
  if ( rf_geomod_deleted_face_has_three_single_neighbor_edges((int)a1, a2) )
  {
    for ( i = 0; i < rf_receiver_get_first_dword(a1 + 30); ++i )
      *(_BYTE *)(*(_DWORD *)sub_552200((_DWORD *)a1 + 30, i) + 28) = 0;
    for ( j = (float *)rf_receiver_get_first_dword(a1 + 28); j; j = (float *)rf_solid_face_next_link((int)j) )
    {
      if ( rf_geomod_face_flag_08000000_is_set((_DWORD *)j + 10) )
        rf_geomod_face_boolean_class_set((int *)j + 10, 0);
    }
    v69 = 0;
    for ( j = (float *)rf_receiver_get_first_dword(a1 + 28); j; j = (float *)rf_solid_face_next_link((int)j) )
    {
      if ( !rf_geomod_face_boolean_class_get((_DWORD *)j + 10) )
      {
        if ( rf_geomod_face_operand_get((_DWORD *)j + 10) && rf_receiver_get_first_dword(a1 + 36) )
          rf_geomod_fragment_classify_spatial_ray(j, a1);
        else
          rf_geomod_fragment_classify_linear_ray(j, a1, 0);
        ++v69;
      }
    }
  }
  dword_D4B908 = 0;
  for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = rf_solid_face_next_link(k) )
  {
    v2 = &rf_geomod_boolean_action_table[40 * rf_geomod_face_operand_get((_DWORD *)(k + 40)) + 5 * a2];
    if ( v2[rf_geomod_face_boolean_class_get((_DWORD *)(k + 40))] == 1
      && !rf_geomod_face_operand_get((_DWORD *)(k + 40))
      && *(_DWORD *)(k + 68) )
    {
      for ( m = 0; m < dword_D4B908 && unk_D4B7F8[m] != *(_DWORD *)(k + 68); ++m )
        ;
      if ( m >= dword_D4B908 )
        unk_D4B7F8[dword_D4B908++] = *(_DWORD *)(k + 68);
    }
  }
  rf_geomod_primary_affected_room = nullptr;
  for ( m = 0; m < dword_D4B908; ++m )
  {
    if ( !rf_geomod_primary_affected_room
      || *(_DWORD *)(unk_D4B7F8[m] + 32) < *((_DWORD *)rf_geomod_primary_affected_room + 8) )
    {
      rf_geomod_primary_affected_room = (float *)unk_D4B7F8[m];
      unk_D4B904 = rf_geomod_primary_affected_room[3];
    }
  }
  for ( m = 0; m < dword_D4B908; ++m )
  {
    if ( *(_DWORD *)(unk_D4B7F8[m] + 4) )
      *(_DWORD *)(*(_DWORD *)(unk_D4B7F8[m] + 4) + 32) = 1;
  }
  for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = rf_solid_face_next_link(k) )
  {
    *(_DWORD *)(k + 40) &= 0xF8FFFFFF;
    *(_DWORD *)(k + 44) = -1;
  }
  for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = link )
  {
    link = rf_solid_face_next_link(k);
    v3 = &rf_geomod_boolean_action_table[40 * rf_geomod_face_operand_get((_DWORD *)(k + 40)) + 5 * a2];
    v19 = v3[rf_geomod_face_boolean_class_get((_DWORD *)(k + 40))];
    switch ( v19 )
    {
      case 1:
        if ( a2 == 4 )
        {
          if ( rf_geomod_face_operand_get((_DWORD *)(k + 40)) )
          {
            *(_DWORD *)(k + 40) |= 0x4000000u;
          }
          else
          {
            rf_geomod_face_set_portal_marker_one((_WORD *)(k + 40));
            v66 = rf_geomod_face_clone_reversed((_DWORD *)k, (int)a1);
            rf_geomod_face_set_portal_marker_one((_WORD *)v66 + 20);
            rf_geomod_boolean_workspace_face_prepend((_DWORD *)a1 + 28, (int)v66);
          }
        }
        else if ( rf_geomod_face_operand_get((_DWORD *)(k + 40))
               || *(float **)(k + 68) == rf_geomod_primary_affected_room
               || !rf_geomod_primary_affected_room
               || !*(_DWORD *)(k + 68) )
        {
          *(_DWORD *)(k + 40) |= 0x4000000u;
        }
        else
        {
          v65 = rf_geomod_face_clone_reversed((_DWORD *)k, (int)a1);
          rf_geomod_room_face_attach(rf_geomod_primary_affected_room, (int)v65);
          rf_geomod_boolean_workspace_face_prepend((_DWORD *)a1 + 28, (int)v65);
          *(_DWORD *)(k + 40) |= (unsigned int)&unk_1000000;
          v65[10] |= (unsigned int)&unk_2000000;
          *(_DWORD *)(k + 44) = *(_DWORD *)(*(_DWORD *)(k + 68) + 32);
          v65[11] = *(_DWORD *)(*(_DWORD *)(k + 68) + 32);
        }
        break;
      case 2:
        if ( rf_geomod_face_operand_get((_DWORD *)(k + 40)) && a2 == 5 )
          rf_geomod_face_set_portal_marker_one((_WORD *)(k + 40));
        break;
      case 3:
        rf_geomod_face_reverse_winding(k);
        if ( rf_geomod_face_operand_get((_DWORD *)(k + 40)) && a2 == 5 )
          rf_geomod_face_set_portal_marker_one((_WORD *)(k + 40));
        break;
    }
  }
  if ( rf_geomod_primary_affected_room )
  {
    for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = rf_solid_face_next_link(k) )
    {
      if ( rf_geomod_face_operand_get((_DWORD *)(k + 40)) && !*(_DWORD *)(k + 68) )
        rf_geomod_room_face_attach(rf_geomod_primary_affected_room, k);
    }
  }
  if ( v73 )
  {
    for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = rf_solid_face_next_link(k) )
    {
      if ( rf_geomod_face_operand_get((_DWORD *)(k + 40)) )
      {
        *(_DWORD *)(k + 40) |= 0x4000000u;
      }
      else
      {
        if ( ((unsigned int)&unk_2000000 & *(_DWORD *)(k + 40)) != 0 )
          v4 = *(_DWORD *)(k + 40) | 0x4000000;
        else
          v4 = *(_DWORD *)(k + 40) & 0xFBFFFFFF;
        *(_DWORD *)(k + 40) = v4;
      }
      *(_DWORD *)(k + 40) &= 0xFCFFFFFF;
    }
  }
  for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = v64 )
  {
    v64 = rf_solid_face_next_link(k);
    if ( (*(_DWORD *)(k + 40) & 0x4000000) != 0 && !rf_geomod_face_operand_get((_DWORD *)(k + 40)) )
    {
      rf_geomod_face_decal_polygons_remove((_DWORD *)k);
      rf_solid_face_list_remove((int *)a1 + 28, k);
      rf_geomod_face_destroy((_DWORD *)k);
    }
  }
  if ( rf_geomod_primary_affected_room )
  {
    if ( *((_BYTE *)rf_geomod_primary_affected_room + 388) )
    {
      rf_geomod_primary_affected_room[98] = unk_D4B904
                                          - rf_geomod_primary_affected_room[3]
                                          + rf_geomod_primary_affected_room[98];
      v60 = rf_geomod_primary_affected_room[3] + rf_geomod_primary_affected_room[98];
      v63 = *(float *)(unk_D4B7C8 + 96) * unk_D4B8E8;
      v61 = *(float *)(unk_D4B7D0 + 4) - v63;
      v62 = *(float *)(unk_D4B7D0 + 4) + v63;
      if ( v60 < (double)v62 && v60 > (double)v61 )
      {
        rf_vector_construct_no_unwind(v56, 0xCu, 4, rf_vector3_default_construct_noop);
        rf_vector3_copy_return_destination(v47, rf_geomod_primary_affected_room + 2);
        rf_vector3_copy_return_destination(v40, rf_geomod_primary_affected_room + 5);
        v50 = rf_geomod_primary_affected_room[3] + rf_geomod_primary_affected_room[98];
        rf_geomod_face_metadata_init(v52);
        v52[0] |= 4u;
        rf_face_metadata_set_flag_40_lowbyte(v52, 1);
        if ( *((int *)rf_geomod_primary_affected_room + 102) < 0 )
        {
          generated_handle_unchecked = *((_DWORD *)rf_geomod_primary_affected_room + 101);
          rf_bitmap_get_resolved_dimensions(*((_DWORD *)rf_geomod_primary_affected_room + 101), &v43, &v49);
        }
        else
        {
          v52[0] |= 0x400u;
          generated_handle_unchecked = rf_procedural_bitmap_get_generated_handle_unchecked(*((_DWORD *)rf_geomod_primary_affected_room
                                                                                           + 102));
          rf_procedural_bitmap_get_dimensions_unchecked(*((_DWORD *)rf_geomod_primary_affected_room + 102), &v43, &v49);
        }
        rf_vector3_set_components_return_destination(v42, v47[0], v50, v48);
        rf_vector3_set_components_return_destination(v54, v47[0], v50, v41);
        rf_vector3_set_components_return_destination(v36, v40[0], v50, v48);
        rf_vector3_set_components_return_destination((float *)v57, v40[0], v50, v41);
        v58 = rf_vector_distance(v42, v54);
        v37 = rf_vector_distance(v42, v36);
        v38 = (double)*((int *)rf_geomod_primary_affected_room + 103) * v58 / (double)v43;
        v45 = (double)*((int *)rf_geomod_primary_affected_room + 104) * v37 / (double)v49;
        rf_vector3_set_components_return_destination(v55, 0.0, 0.0, 0.0);
        rf_vector3_set_components_return_destination(v44, v38, 0.0, 0.0);
        rf_vector3_set_components_return_destination(v51, v38, 0.0, v45);
        rf_vector3_set_components_return_destination(v39, 0.0, 0.0, v45);
        rf_matrix3_construct((char *)v59);
        rf_matrix3_set_euler_angles(v59, 0.0, 0.0, rf_geomod_primary_affected_room[105]);
        rf_matrix3_inverse_rotate_vector(v55, v59);
        rf_matrix3_inverse_rotate_vector(v44, v59);
        rf_matrix3_inverse_rotate_vector(v39, v59);
        rf_matrix3_inverse_rotate_vector(v51, v59);
        v46 = (float *)rf_geomod_face_allocate(v52);
        v15 = v44[2];
        v11 = v44[0];
        v5 = rf_solid_vertex_copy_append(a1, v54);
        rf_geomod_face_corner_append(v46, (int)v5, v11, v15, 0.0, 0.0);
        v16 = v51[2];
        v12 = v51[0];
        v6 = rf_solid_vertex_copy_append(a1, (float *)v57);
        rf_geomod_face_corner_append(v46, (int)v6, v12, v16, 0.0, 0.0);
        v17 = v39[2];
        v13 = v39[0];
        v7 = rf_solid_vertex_copy_append(a1, v36);
        rf_geomod_face_corner_append(v46, (int)v7, v13, v17, 0.0, 0.0);
        v18 = v55[2];
        v14 = v55[0];
        v8 = rf_solid_vertex_copy_append(a1, v42);
        rf_geomod_face_corner_append(v46, (int)v8, v14, v18, 0.0, 0.0);
        rf_geomod_face_finalize_geometry((int)v46, 0, 0);
        rf_geomod_candidate_pair_count = 0;
        for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = rf_solid_face_next_link(k) )
        {
          rf_geomod_face_boolean_class_set((int *)(k + 40), 1);
          if ( rf_geomod_face_operand_get((_DWORD *)(k + 40)) && rf_geomod_face_bounds_overlap((float *)k, v46) )
            rf_geomod_candidate_pair_append(k, (int)v46);
        }
        rf_geomod_room_face_attach(rf_geomod_primary_affected_room, (int)v46);
        rf_geomod_boolean_workspace_face_prepend((_DWORD *)a1 + 28, (int)v46);
        rf_geomod_face_set_boolean_scratch_bit27((unsigned int *)v46 + 10, 0);
        rf_geomod_face_boolean_class_set((int *)v46 + 10, 0);
        rf_geomod_face_set_operand_exact_one((unsigned int *)v46 + 10, 0);
        rf_geomod_boolean_stage_2_split((_DWORD *)dword_D4B88C, 1, 1);
        for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = v35 )
        {
          v35 = rf_solid_face_next_link(k);
          if ( !rf_geomod_face_operand_get((_DWORD *)(k + 40)) && !rf_geomod_face_boolean_class_get((_DWORD *)(k + 40)) )
          {
            ++unk_D4B7F4;
            v34 = rf_geomod_fragment_classify_linear_ray((float *)k, a1, 0);
            ++unk_D4B8E0;
            if ( v34 && rf_geomod_face_boolean_class_get((_DWORD *)(k + 40)) == 1 )
            {
              v33 = rf_geomod_face_clone_reversed((_DWORD *)k, (int)a1);
              rf_geomod_room_face_attach(rf_geomod_primary_affected_room, (int)v33);
              rf_geomod_boolean_workspace_face_prepend((_DWORD *)a1 + 28, (int)v33);
            }
            else
            {
              rf_solid_face_list_remove((int *)a1 + 28, k);
              rf_geomod_face_destroy((_DWORD *)k);
            }
          }
        }
      }
    }
  }
  for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = v32 )
  {
    v32 = rf_solid_face_next_link(k);
    if ( (*(_DWORD *)(k + 40) & 0x4000000) != 0 && rf_geomod_face_operand_get((_DWORD *)(k + 40)) )
    {
      rf_solid_face_list_remove((int *)a1 + 28, k);
      rf_geomod_face_destroy((_DWORD *)k);
    }
  }
  for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = v31 )
  {
    v31 = rf_solid_face_next_link(k);
    if ( (*(_DWORD *)(k + 40) & 0x3000000) != 0 )
    {
      v30 = *(_DWORD *)sub_552200((_DWORD *)a1 + 36, *(_DWORD *)(k + 44));
      rf_world_assign_face_runtime_room_portal(a1, k, v30, (int)rf_geomod_primary_affected_room);
    }
  }
  for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = rf_solid_face_next_link(k) )
  {
    if ( rf_geomod_face_operand_get((_DWORD *)(k + 40)) )
    {
      if ( a2 != 6 )
        rf_geomod_generated_uv_project(k);
      if ( *(__int16 *)(k + 54) < 0 )
      {
        *(_WORD *)(k + 54) = -1;
        rf_geomod_face_lightmap_generate(a1, k, 4.0);
      }
    }
  }
  for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = v29 )
  {
    v29 = rf_solid_face_next_link(k);
    rf_solid_face_list_remove((int *)a1 + 28, k);
    rf_solid_face_list_append(&dword_D4C528, k);
  }
  *((_DWORD *)a1 + 28) = dword_D4C528;
  *((_DWORD *)a1 + 29) = unk_D4C52C;
  result = rf_intrusive_list_reset_head_tail(&dword_D4C528);
  unk_15A7158 = 0;
  if ( rf_geomod_primary_affected_room )
  {
    if ( *((_DWORD *)rf_geomod_primary_affected_room + 15) )
      rf_room_spatial_tree_insert_unowned_faces(
        *((void **)rf_geomod_primary_affected_room + 15),
        rf_geomod_primary_affected_room + 10);
    else
      rf_room_face_spatial_tree_rebuild((int *)rf_geomod_primary_affected_room);
    result = (_DWORD *)rf_solid_finalize_bounds(a1);
  }
  for ( m = 0; m < dword_D4B908; ++m )
  {
    v28 = unk_D4B7F8[m];
    for ( n = 0; ; ++n )
    {
      first_dword = rf_receiver_get_first_dword(a1 + 42);
      if ( n >= first_dword )
        break;
      v26 = 0;
      v24 = *(float **)sub_552200((_DWORD *)a1 + 42, n);
      if ( !rf_pointer_array_count_matches((_DWORD *)(v28 + 108), (int)v24)
        && rf_aabb_overlap_inclusive(v24 + 2, v24 + 5, (float *)(v28 + 8), (float *)(v28 + 20)) )
      {
        for ( ii = rf_receiver_get_first_dword(v24 + 10); ii; ii = rf_face_next_room_link(ii) )
        {
          if ( rf_aabb_overlap_inclusive(
                 (float *)(ii + 16),
                 (float *)(ii + 28),
                 (float *)(v28 + 8),
                 (float *)(v28 + 20)) )
          {
            for ( jj = rf_receiver_get_first_dword((void *)(v28 + 40)); jj; jj = rf_face_next_room_link(jj) )
            {
              if ( rf_aabb_overlap_inclusive(
                     (float *)(ii + 16),
                     (float *)(ii + 28),
                     (float *)(jj + 16),
                     (float *)(jj + 28)) )
              {
                rf_pointer_array_append_dword((_DWORD *)(v28 + 108), (int)v24);
                v26 = 1;
                break;
              }
            }
            if ( v26 )
              break;
          }
        }
        if ( !v26 )
        {
          v22 = rf_receiver_get_first_dword(v24 + 10);
          if ( v22 )
          {
            rf_vector3_copy_return_destination(v21, **(float ***)(v22 + 64));
            v20 = rf_world_resolve_cached_room(a1, nullptr, v21, v21, 0);
            if ( v20 == (void *)v28 )
              rf_pointer_array_append_dword((_DWORD *)(v28 + 108), (int)v24);
          }
        }
      }
    }
    result = (_DWORD *)(m + 1);
  }
  return result;
}

