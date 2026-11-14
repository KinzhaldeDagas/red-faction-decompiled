// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E7A10 rf_player_update_fpgun_presentation
// Advances fpgun presentation and consumes Entity +0x810 bit 0x2 or Player +0xB0 as semantic jump requests under zoom/acceleration/custom-action gates.
// UNREALRED VERIFIED [weapon-holding-variants] Updates the local first-person gun. Base placement selects WeaponInfo+0x58 only when split-screen runtime is active and Player+0xDC is nonzero; otherwise it selects WeaponInfo+0x4C, then rotates by camera orientation and adds camera position before sway/pivot processing.
char __cdecl rf_player_update_fpgun_presentation(int player)
{
  int v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float v6; // [esp+28h] [ebp-178h]
  float v7[3]; // [esp+2Ch] [ebp-174h] BYREF
  float v8[3]; // [esp+38h] [ebp-168h] BYREF
  float v9[3]; // [esp+44h] [ebp-15Ch] BYREF
  float out_vector[3]; // [esp+50h] [ebp-150h] BYREF
  float v11[3]; // [esp+5Ch] [ebp-144h] BYREF
  float copy_result[3]; // [esp+68h] [ebp-138h] BYREF
  unsigned int v13; // [esp+74h] [ebp-12Ch]
  int **v14; // [esp+78h] [ebp-128h]
  int v15; // [esp+7Ch] [ebp-124h]
  int v16; // [esp+80h] [ebp-120h] BYREF
  int k; // [esp+84h] [ebp-11Ch]
  int v18; // [esp+88h] [ebp-118h] BYREF
  char v19; // [esp+8Fh] [ebp-111h]
  int j; // [esp+90h] [ebp-110h]
  char v21; // [esp+97h] [ebp-109h]
  unsigned int v22; // [esp+98h] [ebp-108h]
  int v23; // [esp+9Ch] [ebp-104h]
  _DWORD v24[3]; // [esp+A0h] [ebp-100h]
  int i; // [esp+ACh] [ebp-F4h]
  char v26[36]; // [esp+B0h] [ebp-F0h] BYREF
  float v27; // [esp+D4h] [ebp-CCh]
  float v28; // [esp+D8h] [ebp-C8h]
  float v29; // [esp+DCh] [ebp-C4h]
  float v30[3]; // [esp+E0h] [ebp-C0h] BYREF
  float v31[3]; // [esp+ECh] [ebp-B4h] BYREF
  char v32[36]; // [esp+F8h] [ebp-A8h] BYREF
  float v33; // [esp+11Ch] [ebp-84h]
  float v34; // [esp+120h] [ebp-80h]
  float v35; // [esp+124h] [ebp-7Ch]
  float lhs[3]; // [esp+128h] [ebp-78h] BYREF
  _BYTE v37[36]; // [esp+134h] [ebp-6Ch] BYREF
  float rhs[3]; // [esp+158h] [ebp-48h] BYREF
  float source[3]; // [esp+164h] [ebp-3Ch] BYREF
  float v40[3]; // [esp+170h] [ebp-30h] BYREF
  float v41[3]; // [esp+17Ch] [ebp-24h] BYREF
  _BYTE v42[15]; // [esp+188h] [ebp-18h] BYREF
  char v43; // [esp+197h] [ebp-9h]
  int selected_weapon_and_resolve_mesh; // [esp+198h] [ebp-8h]
  int v45; // [esp+19Ch] [ebp-4h]

  LOBYTE(v1) = player;
  if ( player == rf_local_fpgun_player )
  {
    v1 = rf_entity_resolve_handle(*(_DWORD *)(player + 20));
    v45 = v1;
    if ( v1 )
    {
      selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)player);
      if ( *(int *)(player + 52) > 0 && selected_weapon_and_resolve_mesh >= 0 )
      {
        if ( rf_splitscreen_runtime_active && *(_DWORD *)(player + 220) )
          rf_vector_copy(
            (float *)(player + 4120),
            copy_result,
            (const float *)&rf_weapon_records_first_person_offset_ss + 340 * selected_weapon_and_resolve_mesh);
        else
          rf_vector_copy(
            (float *)(player + 4120),
            v11,
            (const float *)&rf_weapon_records_first_person_offset + 340 * selected_weapon_and_resolve_mesh);
        rf_vector_rotate_by_matrix3((float *)(player + 4120), (float *)(v45 + 2016));
        rf_vector_accumulate((float *)(player + 4120), (float *)(v45 + 2004));
        if ( rf_fpgun_sway_is_eligible(player) )
        {
          rf_matrix3_copy_construct((int)v37, (const void *)(v45 + 2016));
          v34 = rf_frame_delta_seconds * 0.699999988079071;
          v33 = *(float *)(player + 4132) - *(float *)(player + 4136);
          if ( v33 <= 0.0 )
          {
            if ( v33 < -v34 )
              v33 = -v34;
          }
          else if ( v34 < (double)v33 )
          {
            v33 = v34;
          }
          v35 = *(float *)(player + 4140) - *(float *)(player + 4144);
          if ( v35 <= 0.0 )
          {
            if ( v35 < -v34 )
              v35 = -v34;
          }
          else if ( v34 < (double)v35 )
          {
            v35 = v34;
          }
          *(float *)(player + 4136) = *(float *)(player + 4136) + v33;
          *(float *)(player + 4144) = *(float *)(player + 4144) + v35;
          rf_matrix3_copy((float *)(player + 4084), (const float *)(v45 + 2016));
          rf_matrix3_rotate_forward_about_up_axis((float *)(player + 4084), *(float *)(player + 4144));
          rf_matrix3_rotate_up_about_right_axis((float *)(player + 4084), *(float *)(player + 4136));
          rf_vector3_default_construct_noop(lhs);
          rf_vector3_default_construct_noop(rhs);
          rf_matrix3_construct(v32);
          rf_vmesh_compose_prop_world_transform(
            *(_DWORD *)(player + 52),
            *(_DWORD *)(player + 4148),
            (float *)(v45 + 2016),
            player + 4120,
            (int)v32,
            lhs);
          rf_vmesh_compose_prop_world_transform(
            *(_DWORD *)(player + 52),
            *(_DWORD *)(player + 4148),
            (float *)(player + 4084),
            player + 4120,
            (int)v32,
            rhs);
          v2 = rf_vector_subtract(lhs, out_vector, rhs);
          rf_vector_accumulate((float *)(player + 4120), v2);
        }
        else
        {
          *(float *)(player + 4132) = 0.0;
          *(float *)(player + 4140) = 0.0;
          v28 = rf_frame_delta_seconds * 0.699999988079071;
          v27 = *(float *)(player + 4132) - *(float *)(player + 4136);
          if ( v27 <= 0.0 )
          {
            if ( v27 < -v28 )
              v27 = -v28;
          }
          else if ( v28 < (double)v27 )
          {
            v27 = v28;
          }
          v29 = *(float *)(player + 4140) - *(float *)(player + 4144);
          if ( v29 <= 0.0 )
          {
            if ( v29 < -v28 )
              v29 = -v28;
          }
          else if ( v28 < (double)v29 )
          {
            v29 = v28;
          }
          *(float *)(player + 4136) = *(float *)(player + 4136) + v27;
          *(float *)(player + 4144) = *(float *)(player + 4144) + v29;
          rf_matrix3_copy((float *)(player + 4084), (const float *)(v45 + 2016));
          rf_matrix3_rotate_forward_about_up_axis((float *)(player + 4084), *(float *)(player + 4144));
          rf_matrix3_rotate_up_about_right_axis((float *)(player + 4084), *(float *)(player + 4136));
          rf_vector3_default_construct_noop(v30);
          rf_vector3_default_construct_noop(v31);
          rf_matrix3_construct(v26);
          rf_vmesh_compose_prop_world_transform(
            *(_DWORD *)(player + 52),
            *(_DWORD *)(player + 4148),
            (float *)(v45 + 2016),
            player + 4120,
            (int)v26,
            v30);
          rf_vmesh_compose_prop_world_transform(
            *(_DWORD *)(player + 52),
            *(_DWORD *)(player + 4148),
            (float *)(player + 4084),
            player + 4120,
            (int)v26,
            v31);
          v3 = rf_vector_subtract(v30, v9, v31);
          rf_vector_accumulate((float *)(player + 4120), v3);
        }
        rf_entity_view_copy_referenced_position(source, *(_DWORD *)(player + 196));
        rf_entity_view_copy_referenced_matrix_2016((int)v40, *(_DWORD **)(player + 196));
        v4 = rf_vector_subtract(source, v8, (const float *)(player + 4036));
        if ( rf_vector3_length(v4) > 0.05000000074505806
          || rf_vector_dot((float *)(player + 4072), (float *)v42) < 0.9998999834060669
          || rf_vector_dot((float *)(player + 4060), v41) < 0.9998999834060669 )
        {
          sub_4EBD20(player);
        }
        rf_vector_copy((float *)(player + 4036), v7, source);
        rf_matrix3_copy((float *)(player + 4048), v40);
        if ( *(_BYTE *)(player + 3988) == 1 )
          sub_4EBD20(player);
        if ( rf_replicator_has_elapsed((int *)(player + 60)) )
        {
          v23 = 0;
          for ( i = 0; i < 3; ++i )
          {
            if ( rf_weapon_has_loaded_fpgun_action_animation(selected_weapon_and_resolve_mesh, i + 3) )
              v24[v23++] = i + 3;
          }
          if ( v23 > 0 )
          {
            v22 = rand() % v23 + 3;
            rf_fpgun_dispatch_semantic_action(player, v22);
            sub_4EBD20(player);
          }
        }
        if ( rf_replicator_has_elapsed((int *)(player + 4220)) )
        {
          if ( *(_DWORD *)(v45 + 676) == unk_911C88 )
          {
            v21 = 0;
            for ( j = dword_911F74; (_UNKNOWN *)j != &unk_911CE8; j = *(_DWORD *)(j + 652) )
            {
              if ( *(_DWORD *)(j + 664) == dword_911C78
                && *(_DWORD *)(j + 48) == *(_DWORD *)(v45 + 44)
                && *(float *)(j + 668) > 0.0
                && (*(_DWORD *)(j + 124) & 2) == 0 )
              {
                v21 = 1;
                break;
              }
            }
            if ( !v21 && *(int *)(v45 + 4 * dword_912024[340 * dword_911C78] + 684) > 0 )
              rf_player_request_weapon_switch(player, dword_911C78, 0, 0);
          }
          rf_replicator_reset((_DWORD *)(player + 4220));
        }
        rf_fpgun_update_state_transition(player, selected_weapon_and_resolve_mesh);
        if ( *(_DWORD *)(player + 52) )
        {
          if ( rf_multiplayer_runtime_mode && rf_fpgun_draw_or_holster_action_is_active(player) )
          {
            v6 = rf_frame_delta_seconds * 1.5;
            rf_vfx_update_instance(*(int **)(player + 52), v6, 0, player + 4120, player + 4084, 1);
          }
          else
          {
            rf_vfx_update_instance(*(int **)(player + 52), rf_frame_delta_seconds, 0, player + 4120, player + 4084, 1);
          }
          if ( *(_DWORD *)(player + 52) != *(_DWORD *)(player + 56) )
          {
            *(_DWORD *)(player + 64) = rf_model_handle_find_node_adapter(*(_DWORD *)(player + 52), "Muzzle_1");
            *(_DWORD *)(player + 68) = rf_model_handle_find_node_adapter(*(_DWORD *)(player + 52), "Muzzle_2");
            *(_DWORD *)(player + 72) = rf_model_handle_find_node_adapter(*(_DWORD *)(player + 52), "ammo_digit_1");
            *(_DWORD *)(player + 76) = rf_model_handle_find_node_adapter(*(_DWORD *)(player + 52), "ammo_digit_2");
            *(_DWORD *)(player + 4148) = rf_model_handle_find_node_adapter(*(_DWORD *)(player + 52), "pivot_1");
            *(_DWORD *)(player + 56) = *(_DWORD *)(player + 52);
          }
        }
      }
      if ( *(_DWORD *)(player + 3968) != -1
        && !rf_fpgun_action_is_active(player, 7u)
        && !rf_replicator_is_armed((_DWORD *)(player + 3972)) )
      {
        rf_replicator_arm_milliseconds((int *)(player + 3972), 150);
      }
      v43 = 0;
      if ( !rf_fpgun_has_reload_fire_or_riotstick_state2((_DWORD *)player)
        && !rf_fpgun_draw_or_holster_action_is_active(player)
        && !rf_fpgun_custom_action_busy(player) )
      {
        v43 = 1;
      }
      if ( (*(_DWORD *)(v45 + 2064) & 2) != 0 )
      {
        if ( v43 )
          rf_fpgun_dispatch_semantic_action(player, 9u);
        *(_DWORD *)(v45 + 2064) &= ~2u;
      }
      if ( *(_BYTE *)(player + 176) == 1 )
      {
        if ( v43 )
          rf_fpgun_dispatch_semantic_action(player, 9u);
        *(_BYTE *)(player + 176) = 0;
      }
      if ( selected_weapon_and_resolve_mesh == rf_weapon_id_shoulder_cannon )
      {
        rf_model_handle_enable_private_materials_get_table(*(_DWORD *)(player + 52), &v18, &v16);
        if ( dword_662FE8 < 0 )
        {
          for ( k = 0; k < v18; ++k )
          {
            if ( !strcmp((const char *)(v16 + 200 * k + 20), "screen2.tga") )
            {
              if ( *(_DWORD *)(v16 + 200 * k + 188) )
                **(float **)(v16 + 200 * k + 188) = 0.69999999;
              dword_662FE8 = k;
            }
          }
        }
        v19 = 1;
        if ( rf_entity_reload_in_progress(v45) )
        {
          v19 = 0;
        }
        else if ( *(int *)(v45 + 4 * selected_weapon_and_resolve_mesh + 812) <= 0 )
        {
          v19 = 0;
        }
        if ( dword_662FE8 >= 0 )
        {
          if ( v19 )
            *(_DWORD *)(v16 + 200 * dword_662FE8 + 16) = dword_662FEC;
          else
            *(_DWORD *)(v16 + 200 * dword_662FE8 + 16) = dword_662FF0;
        }
      }
      if ( rf_replicator_has_elapsed((int *)(player + 3972)) )
      {
        v15 = *(_DWORD *)(player + 3968);
        rf_player_apply_weapon_selection_by_class(player, *(_DWORD *)(player + 3968));
        rf_fpgun_request_draw_action((_DWORD *)player);
        if ( sub_4EF770() == 1 && v15 == unk_911C6C )
          rf_undercover_apply_local_weapon_skin_profile();
        *(_DWORD *)(player + 3968) = -1;
        rf_replicator_reset((_DWORD *)(player + 3972));
        *(_BYTE *)(player + 3980) = 1;
      }
      if ( selected_weapon_and_resolve_mesh != -1 )
      {
        v14 = (int **)((char *)&rf_weapon_records + 1360 * selected_weapon_and_resolve_mesh);
        if ( rf_weapon_is_riot_stick(selected_weapon_and_resolve_mesh) && (int)v14[320] > 0 )
          rf_vfx_update_instance(v14[320], rf_frame_delta_seconds, 0, 0, 0, 1);
        if ( (rf_weapon_is_riot_stick(selected_weapon_and_resolve_mesh)
           || rf_weapon_has_flame_flag(selected_weapon_and_resolve_mesh))
          && rf_fpgun_state_is_resident(player, 2)
          && (rf_replicator_has_elapsed((int *)(player + 3984)) || !rf_replicator_is_armed((_DWORD *)(player + 3984))) )
        {
          rf_weapon_decrement_clip_or_reserve_ammo(v45, selected_weapon_and_resolve_mesh);
          rf_replicator_arm_milliseconds(
            (int *)(player + 3984),
            (int)(*((float *)v14 + 36) / (double)(int)v14[34] * 1000.0));
        }
      }
      LOBYTE(v1) = rf_replicator_has_elapsed((int *)(player + 4152));
      if ( (unsigned __int8)v1 == 1 )
      {
        rf_replicator_reset((_DWORD *)(player + 4152));
        v13 = selected_weapon_and_resolve_mesh;
        if ( *(_DWORD *)(player + 3968) != -1 )
          v13 = *(_DWORD *)(player + 3968);
        LOBYTE(v1) = rf_entity_custom_mask142C_has_index(v45, v13);
        *(_BYTE *)(player + 4156) = (unsigned __int8)v1 == 1;
      }
    }
  }
  return v1;
}

