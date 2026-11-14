// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D43E0 rf_weapon_trace_character_clutter_contacts
// UNREALRED VERIFIED [mp-hit-region-decode]: Finds nearest instant or piercing contacts; multiplayer chooses stock AABB versus multi_mesh_collide VMesh admission.
bool __cdecl rf_weapon_trace_character_clutter_contacts(
        float *rhs,
        float *lhs,
        int a3,
        int a4,
        float *destination,
        float a6,
        char a7,
        float a8)
{
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float v12[3]; // [esp+4h] [ebp-1F8h] BYREF
  float v13[3]; // [esp+10h] [ebp-1ECh] BYREF
  float v14[3]; // [esp+1Ch] [ebp-1E0h] BYREF
  float v15[3]; // [esp+28h] [ebp-1D4h] BYREF
  float v16[3]; // [esp+34h] [ebp-1C8h] BYREF
  float v17[3]; // [esp+40h] [ebp-1BCh] BYREF
  float v18[3]; // [esp+4Ch] [ebp-1B0h] BYREF
  float v19[3]; // [esp+58h] [ebp-1A4h] BYREF
  float v20[3]; // [esp+64h] [ebp-198h] BYREF
  float v21[3]; // [esp+70h] [ebp-18Ch] BYREF
  float v22[3]; // [esp+7Ch] [ebp-180h] BYREF
  float v23[3]; // [esp+88h] [ebp-174h] BYREF
  float v24[3]; // [esp+94h] [ebp-168h] BYREF
  float copy_result[3]; // [esp+A0h] [ebp-15Ch] BYREF
  int k; // [esp+ACh] [ebp-150h]
  float v27[3]; // [esp+B0h] [ebp-14Ch] BYREF
  float v28[3]; // [esp+BCh] [ebp-140h] BYREF
  float v29[3]; // [esp+C8h] [ebp-134h] BYREF
  int i; // [esp+D4h] [ebp-128h]
  float v31[2]; // [esp+D8h] [ebp-124h] BYREF
  float v32; // [esp+E0h] [ebp-11Ch]
  float sum_result; // [esp+E4h] [ebp-118h] BYREF
  float v34; // [esp+E8h] [ebp-114h]
  float v35[3]; // [esp+F0h] [ebp-10Ch] BYREF
  int j; // [esp+FCh] [ebp-100h]
  float v37[3]; // [esp+100h] [ebp-FCh] BYREF
  float source[15]; // [esp+10Ch] [ebp-F0h] BYREF
  int v39; // [esp+148h] [ebp-B4h]
  char v40; // [esp+157h] [ebp-A5h]
  float v41; // [esp+158h] [ebp-A4h]
  _BYTE v42[4]; // [esp+15Ch] [ebp-A0h] BYREF
  float v43[7]; // [esp+160h] [ebp-9Ch] BYREF
  float v44[3]; // [esp+17Ch] [ebp-80h] BYREF
  float v45[9]; // [esp+188h] [ebp-74h] BYREF
  float v46[3]; // [esp+1ACh] [ebp-50h] BYREF
  float v47[3]; // [esp+1B8h] [ebp-44h] BYREF
  float v48; // [esp+1C4h] [ebp-38h]
  int v49; // [esp+1C8h] [ebp-34h]
  float out_vector[3]; // [esp+1E4h] [ebp-18h] BYREF
  float v51[3]; // [esp+1F0h] [ebp-Ch] BYREF

  rf_physics_hit_record_construct_noop((char *)source);
  v39 = 0;
  if ( rf_geometry_segment_is_obstructed(rhs, lhs, 36, source) )
  {
    rf_vector_copy(lhs, copy_result, source);
    rf_vector_copy(destination, v24, source);
    *((_DWORD *)destination + 5) = v39;
  }
  v40 = 0;
  rf_vector3_default_construct_noop(v37);
  rf_model_collision_query_construct_noop((char *)v44);
  rf_model_collision_result_construct_noop((int)v42);
  v48 = 0.0;
  rf_vector3_copy_return_destination(v51, rhs);
  rf_vector_subtract(lhs, out_vector, rhs);
  destination[4] = NAN;
  destination[3] = 1000000000.0;
  if ( !rf_multiplayer_bbox_hit_regions_enabled || a7 )
  {
    for ( i = dword_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
    {
      if ( !rf_object_has_respawn_inactive_flag(i)
        && (*(_DWORD *)(i + 124) & 2) == 0
        && !rf_entity_is_dead(i)
        && i != a3
        && i != a4 )
      {
        rf_vector3_copy_return_destination(v29, (float *)(i + 400));
        rf_vector3_copy_return_destination(v28, (float *)(i + 412));
        rf_vector_subtract(v29, v27, v28);
        rf_vector_normalize_reciprocal_sqrt(v27);
        rf_vector3_scale_in_place_return_self(v27, a6);
        rf_vector_subtract_in_place(v29, v27);
        rf_vector_accumulate(v28, v27);
        if ( rf_segment_intersects_aabb(v29, v28, rhs, lhs, v37) )
        {
          rf_vector_copy(v46, v21, v51);
          rf_vector_copy(v47, v20, out_vector);
          v49 = 0;
          rf_vector_copy(v44, v19, (const float *)(i + 228));
          rf_matrix3_copy(v45, (const float *)(i + 252));
          v48 = a6;
          v40 = rf_model_handle_collide_all_adapter(*(_DWORD **)(i + 128), (int)v44, (int)v42, 1);
          if ( v40 )
          {
            rf_vector_rotate_by_matrix3(v43, (float *)(i + 252));
            rf_vector_accumulate(v43, (float *)(i + 228));
            v9 = rf_vector_subtract(v43, v18, rhs);
            v41 = rf_vector3_length(v9);
            if ( destination[3] > (double)v41 )
            {
              destination[5] = 0.0;
              destination[4] = *(float *)(i + 44);
              destination[3] = v41;
              rf_vector_copy(destination, v17, v43);
            }
          }
        }
      }
    }
  }
  else
  {
    for ( j = dword_68211C; (_UNKNOWN *)j != &unk_681E90; j = *(_DWORD *)(j + 652) )
    {
      if ( !rf_object_has_respawn_inactive_flag(j)
        && (*(_DWORD *)(j + 124) & 2) == 0
        && !rf_entity_is_dead(j)
        && j != a3
        && j != a4 )
      {
        rf_vector3_copy_return_destination(v31, &flt_87BEF0);
        v31[0] = v31[0] * a8;
        v32 = v32 * a8;
        rf_vector_subtract((const float *)(j + 228), v35, v31);
        rf_vector_add((const float *)(j + 228), &sum_result, v31);
        if ( rf_entity_is_crouched_state810(j) )
          v34 = v34 - unk_87BEF4 * 0.5;
        if ( rf_segment_intersects_aabb(v35, &sum_result, rhs, lhs, v37) )
        {
          v8 = rf_vector_subtract(v37, v23, rhs);
          v41 = rf_vector3_length(v8);
          if ( destination[3] > (double)v41 )
          {
            destination[5] = 0.0;
            destination[4] = *(float *)(j + 44);
            destination[3] = v41;
            rf_vector_copy(destination, v22, v37);
          }
        }
      }
    }
  }
  for ( k = rf_clutter_list_head; (_UNKNOWN *)k != &unk_666D18; k = *(_DWORD *)(k + 652) )
  {
    if ( !rf_object_has_respawn_inactive_flag(k)
      && k != a3
      && k != a4
      && rf_segment_intersects_aabb((float *)(k + 400), (float *)(k + 412), rhs, lhs, v37) )
    {
      rf_vector_copy(v46, v16, v51);
      rf_vector_copy(v47, v15, out_vector);
      v49 = 0;
      rf_vector_copy(v44, v14, (const float *)(k + 228));
      rf_matrix3_copy(v45, (const float *)(k + 252));
      v48 = a6;
      v40 = rf_model_handle_collide_all_adapter(*(_DWORD **)(k + 128), (int)v44, (int)v42, 1);
      if ( v40 )
      {
        rf_vector_rotate_by_matrix3(v43, (float *)(k + 252));
        rf_vector_accumulate(v43, (float *)(k + 228));
        v10 = rf_vector_subtract(v43, v13, rhs);
        v41 = rf_vector3_length(v10);
        if ( destination[3] > (double)v41 )
        {
          destination[5] = 0.0;
          destination[4] = *(float *)(k + 44);
          destination[3] = v41;
          rf_vector_copy(destination, v12, v43);
        }
      }
    }
  }
  return *((int *)destination + 4) >= 0 || *((_DWORD *)destination + 5);
}

