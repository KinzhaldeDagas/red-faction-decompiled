// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050EBB0 rf_projectile_create_runtime
// UNREALRED VERIFIED [combat-native-followup-20261104]: Projectile trail creation50F1CA supplies projectile handle, parsed definition, current projectile room, pointer to current projectile position as previous point, and explicit enabled1. Native4CDAA0 room query still targets definition source position, while4CD460 later transforms emitted position/direction through the parent. Preserve this phase distinction rather than assuming constructor room lookup uses randomized world spawn origin.
float *__cdecl rf_projectile_create_runtime(int a1, int a2, float *source, float *a4, char a5, int a6)
{
  float *v7; // eax
  float *v8; // eax
  int v9; // eax
  void *first_dword; // eax
  int v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float *v18; // [esp+18h] [ebp-2ACh]
  float v19; // [esp+24h] [ebp-2A0h]
  double v20; // [esp+28h] [ebp-29Ch]
  float scalar; // [esp+30h] [ebp-294h]
  float *v22; // [esp+34h] [ebp-290h]
  float v23[3]; // [esp+38h] [ebp-28Ch] BYREF
  float sum_result[3]; // [esp+44h] [ebp-280h] BYREF
  int v25[3]; // [esp+50h] [ebp-274h] BYREF
  float v26[3]; // [esp+5Ch] [ebp-268h] BYREF
  float v27[3]; // [esp+68h] [ebp-25Ch] BYREF
  float v28[3]; // [esp+74h] [ebp-250h] BYREF
  float v29[3]; // [esp+80h] [ebp-244h] BYREF
  float v30[3]; // [esp+8Ch] [ebp-238h] BYREF
  float out_vector[3]; // [esp+98h] [ebp-22Ch] BYREF
  float v32[3]; // [esp+A4h] [ebp-220h] BYREF
  float v33[3]; // [esp+B0h] [ebp-214h] BYREF
  float v34[3]; // [esp+BCh] [ebp-208h] BYREF
  float v35[3]; // [esp+C8h] [ebp-1FCh] BYREF
  float v36[3]; // [esp+D8h] [ebp-1ECh] BYREF
  float v37[3]; // [esp+E4h] [ebp-1E0h] BYREF
  float v38[3]; // [esp+F0h] [ebp-1D4h] BYREF
  float copy_result[3]; // [esp+FCh] [ebp-1C8h] BYREF
  float scaled_result[3]; // [esp+108h] [ebp-1BCh] BYREF
  float *v41; // [esp+114h] [ebp-1B0h]
  char v42; // [esp+11Bh] [ebp-1A9h]
  _DWORD *i; // [esp+11Ch] [ebp-1A8h]
  float rhs[3]; // [esp+120h] [ebp-1A4h] BYREF
  float v45[3]; // [esp+12Ch] [ebp-198h] BYREF
  char v46[52]; // [esp+138h] [ebp-18Ch] BYREF
  float v47[3]; // [esp+16Ch] [ebp-158h] BYREF
  float v48[13]; // [esp+178h] [ebp-14Ch] BYREF
  float *v49; // [esp+1ACh] [ebp-118h]
  float v50[9]; // [esp+1B0h] [ebp-114h] BYREF
  _DWORD v51[2]; // [esp+1D4h] [ebp-F0h] BYREF
  float lhs[8]; // [esp+1DCh] [ebp-E8h] BYREF
  float *v53; // [esp+1FCh] [ebp-C8h]
  int v54; // [esp+200h] [ebp-C4h]
  float *v55; // [esp+204h] [ebp-C0h]
  int v56; // [esp+208h] [ebp-BCh]
  char v57; // [esp+20Fh] [ebp-B5h]
  float *v58; // [esp+210h] [ebp-B4h]
  char *v59; // [esp+214h] [ebp-B0h]
  void *v60[38]; // [esp+218h] [ebp-ACh] BYREF
  bool v61; // [esp+2B3h] [ebp-11h]
  int v62; // [esp+2B4h] [ebp-10h]
  int v63; // [esp+2C0h] [ebp-4h]

  v57 = 0;
  if ( a1 < 0 || a1 > dword_911C68 )
    return nullptr;
  v59 = (char *)&rf_weapon_records + 1360 * a1;
  v62 = rf_entity_resolve_handle(a2);
  rf_object_setup152_construct_members((char *)v60);
  v63 = 0;
  memset(v60, 0, sizeof(v60));
  if ( (int)rf_string_length_from_cstr((const char **)v59 + 4) <= 4 )
  {
    v60[0] = nullptr;
  }
  else
  {
    v60[0] = (void *)rf_string_object_c_str_or_empty(v59 + 16);
    v60[1] = *((void **)v59 + 6);
  }
  if ( !rf_multiplayer_runtime_mode
    && ((*((_DWORD *)v59 + 153) & 0x400) == 0 || !rf_entity_matches_local_player_or_related_handle(v62))
    && (*((_DWORD *)v59 + 153) & 0x40000000) != 0
    && rf_entity_counter1424_is_nonpositive(v62) )
  {
    v57 = 1;
  }
  v60[5] = *((void **)v59 + 47);
  v60[33] = *((void **)v59 + 43);
  rf_matrix3_copy((float *)&v60[18], a4);
  if ( v57 == 1 )
  {
    scalar = *((float *)v59 + 48) * flt_663AC8;
    v7 = rf_vector_multiply_scalar(a4 + 6, scaled_result, scalar);
    rf_vector_copy((float *)&v60[27], copy_result, v7);
  }
  else
  {
    v8 = rf_vector_multiply_scalar(a4 + 6, v38, *((float *)v59 + 48));
    rf_vector_copy((float *)&v60[27], v37, v8);
  }
  rf_vector_copy((float *)&v60[15], v36, source);
  v60[37] = (void *)-2147481488;
  if ( a1 == rf_weapon_index_grenade || rf_weapon_has_flame_flag(a1) )
  {
    if ( a1 == rf_weapon_index_grenade )
      rf_vector3_set_components_thiscall((float *)&v60[30], 10.0, 0.0, 0.0);
    else
      rf_vector3_set_components_thiscall((float *)&v60[30], 20.0, 0.0, 0.0);
    rf_vector_rotate_by_matrix3((float *)&v60[30], (float *)&v60[18]);
    v60[4] = (void *)2;
  }
  if ( (*((_DWORD *)v59 + 153) & 0x1000) != 0 )
    v60[37] = (void *)((int)v60[37] | 1);
  if ( *((int *)v59 + 153) < 0 )
    v60[37] = (void *)((int)v60[37] | 0x200);
  if ( *((float *)v59 + 48) < 50.0 )
    v60[37] = (void *)((int)v60[37] | 8);
  if ( (*((_DWORD *)v59 + 154) & 0x10) != 0 )
    v60[37] = (void *)((int)v60[37] & ~0x10u);
  v56 = 0x100000;
  v58 = rf_object_create(2, -1, a2, (int)v60, 0x100000, nullptr);
  if ( !v58 )
  {
    v63 = -1;
    rf_object_setup152_destroy_array_backing(v60);
    return nullptr;
  }
  v58[13] = 10.0;
  *((_DWORD *)v58 + 165) = v59;
  *((_DWORD *)v58 + 166) = a1;
  v58[167] = *((float *)v59 + 44);
  *((_DWORD *)v58 + 170) = a6;
  v58[172] = NAN;
  v58[190] = 0.0;
  rf_vector_copy(v58 + 194, v35, source);
  if ( v62 && (*(_DWORD *)(v62 + 2064) & 0x2000) != 0 )
    *((_DWORD *)v58 + 190) |= 1u;
  if ( v57 )
    *((_DWORD *)v58 + 170) |= 4u;
  if ( *((_DWORD *)v58 + 32) )
    rf_object_model_presence_status((int)v58);
  if ( rf_object_has_player_flag(v62) )
    *((_DWORD *)v58 + 170) |= 1u;
  if ( v62 )
    v58[185] = *(float *)(v62 + 504);
  else
    *((_DWORD *)v58 + 185) = 1;
  if ( byte_704E83 == 1 || *(float *)(*((_DWORD *)v58 + 165) + 540) <= 0.0 )
  {
    v58[169] = NAN;
  }
  else
  {
    v9 = rf_renderer_point_light_create(
           (int)source,
           *(float *)(*((_DWORD *)v58 + 165) + 536),
           *(float *)(*((_DWORD *)v58 + 165) + 540),
           *(float *)(*((_DWORD *)v58 + 165) + 544),
           *(float *)(*((_DWORD *)v58 + 165) + 548),
           *(float *)(*((_DWORD *)v58 + 165) + 552),
           1,
           1,
           0);
    *((_DWORD *)v58 + 169) = v9;
  }
  v58[171] = 0.0;
  if ( *(int *)(*((_DWORD *)v58 + 165) + 152) > -1 )
  {
    v55 = (float *)dword_867800[*(_DWORD *)(*((_DWORD *)v58 + 165) + 152)];
    if ( v55 )
    {
      v18 = v58 + 15;
      first_dword = (void *)rf_receiver_get_first_dword(v58);
      v54 = rf_particle_emitter_create(*((_DWORD *)v58 + 11), v55, first_dword, v18, 1);
      if ( v54 )
      {
        *(float *)(v54 + 336) = v58[154];
        *((_DWORD *)v58 + 154) = v54;
      }
    }
  }
  if ( *((int *)v59 + 93) < 0 )
  {
    v58[168] = NAN;
  }
  else
  {
    v11 = rf_gamesound_play_positional_event(*((_DWORD *)v59 + 93), v58 + 15, 1.0, (int)flt_17F10B0, 0);
    *((_DWORD *)v58 + 168) = v11;
  }
  v58[186] = NAN;
  rf_replicator_arm_milliseconds((int *)v58 + 187, 0);
  v58[188] = *((float *)v59 + 159);
  v58[189] = *((float *)v59 + 165);
  *((_DWORD *)v58 + 107) = 4096;
  rf_entity_decrement_counter1424_and_reset_if_negative(v62, *(_DWORD *)(*((_DWORD *)v58 + 165) + 628));
  v61 = 1;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority && byte_663A38 && v62 != dword_681E38 )
    v61 = (*(_DWORD *)(*((_DWORD *)v58 + 165) + 616) & 0x800) == 0;
  if ( v61 )
    rf_collision_register_object_against_active_list((int)v58);
  *((_DWORD *)v58 + 164) = unk_911F78;
  *((_DWORD *)v58 + 163) = &unk_911CE8;
  *(_DWORD *)(unk_911F78 + 652) = v58;
  unk_911F78 = v58;
  if ( a1 == dword_911CE0 )
  {
    v53 = (float *)rf_object_resolve_handle(a2);
    if ( v53 )
    {
      if ( rf_object_is_entity((int)v53) )
      {
        rf_vector3_default_construct_noop(rhs);
        rf_vector3_default_construct_noop(v45);
        rf_matrix3_construct((char *)v50);
        v49 = v53;
        if ( !sub_438AC0((int)v53) || rf_view_wrapper_get_dword8(*(_DWORD *)(*((_DWORD *)v49 + 1292) + 196)) )
          rf_entity_compute_weapon_muzzle_transform(v49, dword_911CE0, rhs, v50);
        else
          rf_player_compose_fpgun_muzzle_world_transform(*((void **)v49 + 1292), rhs, nullptr);
        rf_solid_collision_query_construct_clear_face_hint(v46);
        rf_solid_collision_result_construct_noop((int)v51);
        rf_vector_copy(v47, v34, v49 + 501);
        v12 = rf_vector_multiply_scalar(a4 + 6, v33, 50.0);
        rf_vector_copy(v48, v32, v12);
        v48[3] = 0.0;
        LODWORD(v48[4]) = 4;
        rf_world_collision_sweep((char *)rf_world_solid, (int)v46, (int)v51, 1);
        if ( v51[0] <= 0 )
        {
          rf_vector_copy(v45, v26, v49 + 510);
        }
        else
        {
          v13 = rf_vector_subtract(lhs, out_vector, v49 + 501);
          v20 = rf_vector3_length(v13);
          v14 = rf_vector_subtract(rhs, v30, v49 + 501);
          if ( rf_vector3_length(v14) >= v20 )
          {
            rf_vector_copy(v45, v27, v49 + 510);
          }
          else
          {
            v15 = rf_vector_subtract(lhs, v29, rhs);
            rf_vector_copy(v45, v28, v15);
            rf_vector_normalize(v45);
          }
        }
        rf_rail_trail_allocate_from_pool(*((_DWORD *)v58 + 11), rhs, v45, *((float *)v59 + 48));
      }
    }
  }
  if ( a5 == 1 )
    *((_DWORD *)v58 + 170) |= 0x20u;
  if ( (*(_DWORD *)(*((_DWORD *)v58 + 165) + 612) & 0x20) != 0 )
  {
    v19 = *(float *)(*((_DWORD *)v58 + 165) + 192) * *(float *)(*((_DWORD *)v58 + 165) + 176);
    v16 = rf_vector_scale((float *)v25, v19, v58 + 69);
    v17 = rf_vector_add(v58 + 57, sum_result, v16);
    rf_vector_copy(v58 + 60, v23, v17);
    rf_segment_bounds_build(v58 + 100, v58 + 103, v58 + 57, v58 + 60);
    rf_vector3_subtract_scalar_in_place(v58 + 100, v58[96]);
    rf_vector3_add_scalar_in_place(v58 + 103, v58[96]);
    v42 = 0;
    for ( i = (_DWORD *)rf_receiver_get_first_dword(dword_813BD0);
          ;
          i = (_DWORD *)rf_intrusive_node_get_next_stdcall((int)i) )
    {
      if ( !i )
      {
LABEL_93:
        if ( !v42 )
          rf_physics_world_contacts_sweep((int)v58);
        if ( v42 )
          rf_projectile_contact_response_dispatch((int)v58);
        rf_object_mark_for_deferred_delete((int)v58);
        break;
      }
      if ( (float *)i[1] == v58 )
      {
        v41 = (float *)i[2];
      }
      else
      {
        if ( (float *)i[2] != v58 )
          continue;
        v41 = (float *)i[1];
      }
      if ( rf_aabb_overlap_strict_ordered(v58 + 100, v58 + 103, v41 + 100, v41 + 103) )
      {
        *(float *)(i[1] + 460) = 1.0;
        *(float *)(i[2] + 460) = 1.0;
        if ( (i[3] & 6) != 0 )
        {
          if ( rf_physics_pair_contact_against_model(v58, v41) )
          {
            v42 = 1;
            goto LABEL_93;
          }
        }
        else if ( rf_physics_pair_contact_sphere_samples(v58, v41) )
        {
          v42 = 1;
          goto LABEL_93;
        }
      }
    }
  }
  v22 = v58;
  v63 = -1;
  rf_object_setup152_destroy_array_backing(v60);
  return v22;
}

