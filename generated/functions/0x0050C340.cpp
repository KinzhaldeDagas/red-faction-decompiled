// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050C340 rf_projectile_object_contact
// UNREALRED VERIFIED [combat-level-transport-20260930] In the ordinary contact damage block (projectile+0x2A8 bit0x80 clear), multiplayer mode==1 with server authority false skips hit-region damage, rf_damage_dispatch, and the subsequent radial call. Presentation handling follows outside that gate. Earlier special attached/protected-object branches are separate and are not covered by this statement. Unreal client-trigger transport must therefore verify server contact/pool mutation separately from client predicted fire/presentation.
bool __cdecl rf_projectile_object_contact(int a1)
{
  void *first_dword; // eax
  float *v3; // eax
  float *v4; // eax
  char *v5; // eax
  float *v6; // eax
  const float *v7; // eax
  float *v8; // eax
  char v9; // al
  char v10; // al
  char v11; // al
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int name; // eax
  int v16; // eax
  int v17; // eax
  float *v18; // [esp+4h] [ebp-134h] BYREF
  float *v19; // [esp+8h] [ebp-130h]
  int v20; // [esp+Ch] [ebp-12Ch]
  int strength; // [esp+10h] [ebp-128h]
  int v22; // [esp+14h] [ebp-124h]
  int v23; // [esp+18h] [ebp-120h]
  float v24; // [esp+1Ch] [ebp-11Ch]
  float v25; // [esp+20h] [ebp-118h]
  int v26; // [esp+24h] [ebp-114h]
  BOOL v27; // [esp+28h] [ebp-110h]
  BOOL v28; // [esp+2Ch] [ebp-10Ch]
  float v29[9]; // [esp+34h] [ebp-104h] BYREF
  _BYTE v30[36]; // [esp+58h] [ebp-E0h] BYREF
  float copy_result[3]; // [esp+7Ch] [ebp-BCh] BYREF
  float v32[3]; // [esp+88h] [ebp-B0h] BYREF
  float v33[3]; // [esp+94h] [ebp-A4h] BYREF
  float v34[3]; // [esp+A0h] [ebp-98h] BYREF
  int v35; // [esp+ACh] [ebp-8Ch]
  int v36; // [esp+B0h] [ebp-88h]
  int local_player_entry_or_related_owner; // [esp+B4h] [ebp-84h]
  _DWORD *v38; // [esp+B8h] [ebp-80h]
  int v39; // [esp+BCh] [ebp-7Ch]
  float v40[3]; // [esp+C0h] [ebp-78h] BYREF
  int v41; // [esp+CCh] [ebp-6Ch]
  bool v42; // [esp+D3h] [ebp-65h]
  int v43; // [esp+D4h] [ebp-64h]
  char v44; // [esp+DBh] [ebp-5Dh]
  float v45[2]; // [esp+DCh] [ebp-5Ch] BYREF
  float v46; // [esp+E4h] [ebp-54h]
  int v47; // [esp+E8h] [ebp-50h]
  float v48; // [esp+ECh] [ebp-4Ch]
  int v49; // [esp+F0h] [ebp-48h] BYREF
  int v50; // [esp+F4h] [ebp-44h]
  int v51; // [esp+F8h] [ebp-40h]
  float v52; // [esp+FCh] [ebp-3Ch]
  char v53; // [esp+103h] [ebp-35h] BYREF
  float v54; // [esp+104h] [ebp-34h]
  int v55[2]; // [esp+108h] [ebp-30h] BYREF
  float selected_damage_with_owner_scale; // [esp+110h] [ebp-28h]
  float out_vector[3]; // [esp+114h] [ebp-24h] BYREF
  int v58; // [esp+120h] [ebp-18h]
  bool v59; // [esp+127h] [ebp-11h]
  char *v60; // [esp+128h] [ebp-10h]
  int v61; // [esp+12Ch] [ebp-Ch]
  int v62; // [esp+130h] [ebp-8h] BYREF
  int v63; // [esp+134h] [ebp-4h]

  v59 = 0;
  *(float *)&v62 = 0.0;
  if ( *(_DWORD *)(a1 + 48) == *(_DWORD *)(a1 + 484) )
    return 1;
  if ( *(_DWORD *)(a1 + 688) != -1 )
    return 1;
  v63 = rf_object_resolve_handle(*(_DWORD *)(a1 + 484));
  if ( !v63 )
    return 1;
  if ( *(_DWORD *)(a1 + 48) == *(_DWORD *)(v63 + 512) )
    return 1;
  v60 = (char *)rf_entity_resolve_handle(*(_DWORD *)(v63 + 44));
  if ( v60 && rf_entity_class_flag2000000_positive_scalar56((int)v60) )
  {
    selected_damage_with_owner_scale = rf_projectile_get_selected_damage_with_owner_scale(a1, 0);
    if ( *(_DWORD *)(a1 + 664) == dword_911C78
      || *(_DWORD *)(a1 + 664) == rf_weapon_index_grenade && (*(_DWORD *)(a1 + 680) & 0x10) == 0 )
    {
      selected_damage_with_owner_scale = 0.0;
    }
    else if ( *(_DWORD *)(a1 + 664) == dword_911CE0 )
    {
      selected_damage_with_owner_scale = 100.0;
    }
    if ( (*((_DWORD *)v60 + 31) & 4) == 0 )
    {
      *((float *)v60 + 14) = *((float *)v60 + 14) - selected_damage_with_owner_scale;
      if ( *((float *)v60 + 14) <= 0.0 )
        rf_entity_restore_saved_class_motion_and_clear_source((int)v60, 1);
    }
    if ( selected_damage_with_owner_scale >= 100.0 )
      v58 = unk_681E74;
    else
      v58 = dword_681E64;
    rf_vector_subtract((const float *)(a1 + 436), out_vector, (const float *)v60 + 15);
    v19 = (float *)(v60 + 60);
    v18 = (float *)(v60 + 60);
    first_dword = (void *)rf_receiver_get_first_dword(v60);
    rf_vclip_spawn_runtime_effect(v58, first_dword, v18, v19, COERCE_FLOAT_(1.0), -1, out_vector, 1);
    return 0;
  }
  else
  {
    if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(*(_DWORD *)(a1 + 660) + 612)) != 0 )
    {
      if ( (*(_DWORD *)(a1 + 680) & 0x40) == 0 )
      {
        if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x40) != 0 )
        {
          v3 = rf_vector_negate((float *)(a1 + 448), v34);
          rf_orientation_matrix_from_normalized_direction((float *)(a1 + 72), v3);
          *(float *)(a1 + 668) = *(float *)(*(_DWORD *)(a1 + 660) + 176);
        }
        else
        {
          v4 = rf_vector_negate((float *)(a1 + 448), v33);
          rf_orientation_matrix_from_normalized_direction((float *)(a1 + 72), v4);
        }
        if ( (int)rf_string_length_from_cstr((const char **)(*(_DWORD *)(a1 + 660) + 28)) > 0 )
        {
          rf_object_release_owned_model_handle(a1);
          v23 = 3;
          v5 = (char *)rf_string_object_c_str_or_empty((const void *)(*(_DWORD *)(a1 + 660) + 28));
          rf_object_bind_model_filename_by_kind(a1, v5, 3);
          rf_vfx_start_instance(*(int **)(a1 + 128), 0, 1.0, 1);
        }
        if ( rf_object_is_entity(v63) )
        {
          v55[1] = v63;
          sub_40A3C0((int *)(v63 + 672), *(_DWORD *)(a1 + 48), 0.0, 1);
        }
        *(_DWORD *)(a1 + 688) = *(_DWORD *)(a1 + 484);
        v6 = rf_vector_subtract((const float *)(a1 + 436), v32, (const float *)(v63 + 60));
        rf_vector_copy((float *)(a1 + 692), copy_result, v6);
        rf_matrix3_inverse_rotate_vector((float *)(a1 + 692), (float *)(v63 + 72));
        v7 = (const float *)rf_matrix3_transpose_to_output((float *)(v63 + 72), (int)v30);
        v8 = rf_matrix3_argument_times_receiver_to_output(v7, v29, (const float *)(a1 + 72));
        rf_matrix3_copy((float *)(a1 + 704), v8);
        *(_DWORD *)(a1 + 424) &= ~0x80000000;
        *(_DWORD *)(a1 + 680) |= 0x40u;
      }
      v59 = 1;
    }
    else if ( !rf_multiplayer_runtime_mode
           && !rf_splitscreen_runtime_active
           && rf_object_is_player_associated(v63)
           && rf_projectile_try_play_near_miss_sound(v63, (_DWORD *)a1, a1 + 436) == 1 )
    {
      rf_ai_maybe_queue_jump_for_different_target_owner(v63, a1);
      return 0;
    }
    if ( (*(_DWORD *)(a1 + 680) & 0x80) == 0 )
    {
      v28 = rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority;
      if ( !v28 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x40) == 0 )
      {
        *(float *)&v49 = rf_projectile_get_selected_damage_with_owner_scale(a1, 0);
        v55[0] = -1;
        v50 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 48));
        if ( rf_entity_class_flag2_100(v50) )
          *(float *)&v49 = *(float *)&v49 * 3.0;
        v62 = v49;
        v51 = rf_entity_resolve_handle(*(_DWORD *)(v63 + 44));
        if ( v51 )
        {
          v48 = rf_character_classify_weapon_hit_region(v51, a1, (float *)(a1 + 436), v55);
          *(float *)&v62 = *(float *)&v49 * v48;
          if ( rf_entity_has_humanoid_flag(v51) && !rf_entity_is_dead(v51) )
          {
            v44 = 0;
            v47 = *(_DWORD *)(a1 + 664);
            if ( v47 == rf_weapon_id_rocket_launcher
              || v47 == rf_weapon_id_shoulder_cannon
              || v47 == rf_weapon_id_apc_rocket
              || v47 == rf_weapon_id_fighter_rocket
              || v47 == rf_weapon_id_heap
              || v47 == rf_weapon_id_shotgun )
            {
              if ( v47 == rf_weapon_id_shotgun )
              {
                v43 = rf_object_resolve_handle(*(_DWORD *)(a1 + 48));
                if ( v43 )
                {
                  if ( rf_multiplayer_runtime_mode )
                  {
                    if ( rf_vector_distance_squared((const float *)(v43 + 60), (const float *)(v63 + 60)) < 100.0 )
                      v44 = 1;
                  }
                  else if ( rf_vector_distance_squared((const float *)(v43 + 60), (const float *)(v63 + 60)) < 25.0 )
                  {
                    v44 = 1;
                  }
                }
              }
              else
              {
                v44 = 1;
              }
            }
            rf_vector3_copy_return_destination(v45, (float *)(a1 + 436));
            rf_vector_inverse_translate_rotate_in_place(v45, v51 + 60, v51 + 72);
            if ( v44 == 1 )
            {
              v27 = rf_vector_dot((float *)(a1 + 96), (float *)(v51 + 96)) < 0.0;
              v42 = v27;
              if ( v27 )
                *(_DWORD *)(v51 + 2084) = 7;
              else
                *(_DWORD *)(v51 + 2084) = 6;
            }
            else
            {
              v26 = v55[0];
              if ( v55[0] )
              {
                if ( v26 == 1 )
                {
                  if ( v46 <= 0.0 )
                  {
                    *(_DWORD *)(v51 + 2088) = 25;
                    *(_DWORD *)(v51 + 2084) = 11;
                  }
                  else
                  {
                    *(_DWORD *)(v51 + 2088) = 24;
                    *(_DWORD *)(v51 + 2084) = 12;
                  }
                }
                else if ( v26 == 2 )
                {
                  *(_DWORD *)(v51 + 2084) = v46 <= 0.0 ? 8 : 9;
                  if ( rf_entity_has_model1410_and_runtime_flag200000(v51) )
                    rf_entity_spawn_class_tag_debris((const float *)v51, a1);
                }
              }
              else if ( v45[0] <= 0.0 )
              {
                *(_DWORD *)(v51 + 2088) = 26;
                *(_DWORD *)(v51 + 2084) = 14;
              }
              else
              {
                *(_DWORD *)(v51 + 2088) = 27;
                *(_DWORD *)(v51 + 2084) = 15;
              }
            }
          }
          if ( (*(_DWORD *)(a1 + 680) & 8) != 0 )
          {
            v41 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 48));
            if ( v41 )
            {
              if ( sub_438AC0(v41) )
                rf_replicator_arm_milliseconds((int *)(v41 + 4972), 200);
            }
          }
        }
        if ( rf_projectile_apply_common_object_penetration(a1, (float *)(a1 + 436), v63, (float *)&v62, &v53) )
          v59 = v53 == 0;
        if ( v51 )
        {
          if ( *(_DWORD *)(a1 + 664) == rf_weapon_id_flamethrower && (*(_DWORD *)(a1 + 680) & 0x20) != 0 )
            *(_DWORD *)(v51 + 2068) |= 0x8000u;
          if ( *(_DWORD *)(a1 + 664) == rf_weapon_id_riot_stick && (*(_DWORD *)(a1 + 680) & 0x20) != 0 )
          {
            rf_vector3_copy_return_destination(v40, (float *)(a1 + 436));
            rf_vector_inverse_translate_rotate_in_place(v40, v51 + 60, v51 + 72);
            if ( v40[2] <= 0.0 )
              *(_DWORD *)(v51 + 2084) = 6;
            else
              *(_DWORD *)(v51 + 2084) = 7;
          }
        }
        if ( rf_multiplayer_runtime_mode )
        {
          v39 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 48));
          if ( v39 && (*(_DWORD *)(v39 + 2068) & 0x20000) != 0 )
            *(float *)&v62 = *(float *)&v62 * flt_662DC0;
          if ( v51 && (*(_DWORD *)(v51 + 2068) & 0x40000) != 0 )
          {
            *(float *)&v23 = 0.0;
            *(float *)&v22 = 1.0;
            strength = 87;
            rf_vector3_copy_return_destination((float *)&v18, (float *)(v51 + 60));
            rf_sound_event_play_for_object_view(
              v51,
              *(float *)&v18,
              (int)v19,
              v20,
              strength,
              *(float *)&v22,
              *(float *)&v23);
          }
        }
        v54 = rf_damage_dispatch(
                *(_DWORD *)(v63 + 44),
                *(float *)&v62,
                *(_DWORD *)(a1 + 48),
                *(_DWORD *)(a1 + 664),
                *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1324),
                a1 + 436,
                -1,
                0);
        if ( v51 )
        {
          if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
          {
            v38 = sub_4DD720(*(_DWORD *)(v51 + 44));
            if ( v38 )
            {
              if ( v38 != (_DWORD *)rf_local_fpgun_player )
              {
                v9 = rf_player_direction_to_local_quadrant_mask((int)v38, (float *)(a1 + 96));
                *((_BYTE *)v38 + 4604) = v9;
              }
            }
          }
          if ( sub_438AC0(v51) )
          {
            v10 = rf_player_direction_to_local_quadrant_mask(*(_DWORD *)(v51 + 5168), (float *)(a1 + 96));
            rf_player_or_direction_nibble_into_flags(*(_DWORD *)(v51 + 5168), v10);
          }
          else if ( rf_entity_matches_local_player_or_related_handle(v51) )
          {
            local_player_entry_or_related_owner = rf_object_find_local_player_entry_or_related_owner(v51);
            if ( local_player_entry_or_related_owner )
            {
              v11 = rf_player_direction_to_local_quadrant_mask(local_player_entry_or_related_owner, (float *)(a1 + 96));
              rf_player_or_direction_nibble_into_flags(local_player_entry_or_related_owner, v11);
              if ( rf_object_is_use_vehicle((_DWORD *)v51) && unk_91252C[340 * *(_DWORD *)(a1 + 664)] == 3 )
              {
                rf_float_clamp_in_place((float *)&v49, 0.0, 100.0);
                v25 = *(float *)&v49 * 0.01999999955296516;
                *(float *)&v23 = v25;
                v24 = *(float *)&v49 * 0.00009999999747378752;
                rf_entity_set_player_linked_perturbation_timer(
                  *(_DWORD *)(local_player_entry_or_related_owner + 196),
                  v24,
                  v25);
              }
            }
          }
          if ( *(float *)(v63 + 52) <= 0.0
            && *(_DWORD *)(v63 + 508) == 3
            && (unk_91252C[340 * *(_DWORD *)(a1 + 664)] == 1 || unk_91252C[340 * *(_DWORD *)(a1 + 664)] == 2) )
          {
            if ( v55[0] == 2 )
            {
              *(_DWORD *)(v63 + 2064) |= 0x8000000u;
            }
            else if ( v55[0] == 1 )
            {
              *(_DWORD *)(v63 + 2064) |= 0x10000000u;
            }
          }
        }
        v52 = rf_projectile_get_selected_damage_with_owner_scale(a1, 0);
        rf_damage_apply_radial(
          (float *)(a1 + 436),
          v52,
          *(float *)(*(_DWORD *)(a1 + 660) + 520),
          *(_DWORD *)(a1 + 48),
          4 - (rf_weapon_id_flamethrower != *(_DWORD *)(a1 + 664)));
      }
    }
    v61 = -1;
    if ( byte_704E83 != 1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x40) == 0 )
    {
      if ( *(_DWORD *)(v63 + 508) == 3 )
      {
        if ( *(float *)(*(_DWORD *)(a1 + 660) + 332) > 1.0 )
        {
          v23 = *(int *)(a1 + 48);
          v22 = a1 + 448;
          strength = a1 + 436;
          v20 = a1 + 60;
          v12 = rf_receiver_get_first_dword((void *)a1);
          rf_weapon_spawn_impact_vclips(*(_DWORD *)(a1 + 664), v12, v20, strength, v22, v23);
          rf_weapon_create_impact_decal(
            *(_DWORD *)(a1 + 664),
            (const float *)(a1 + 436),
            (const float *)(a1 + 324),
            (const float *)(a1 + 448),
            *(_DWORD *)(a1 + 484),
            0,
            0);
        }
        if ( (*(_DWORD *)(a1 + 680) & 8) == 0 )
        {
          if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x20) == 0 )
            rf_blood_decal_trace_and_submit(*(float *)&v62, (const float *)(a1 + 436), (const float *)(a1 + 96));
          if ( !rf_entity_has_player_pointer_if_type0(v63) )
          {
            v23 = v62;
            v22 = v63 + 60;
            v13 = rf_receiver_get_first_dword((void *)v63);
            rf_spawn_gray_particle_and_vclip((float *)(a1 + 436), v13, v22, *(float *)&v23);
          }
        }
      }
      else if ( !rf_entity_matches_local_player_or_related_handle(v63) )
      {
        v23 = *(int *)(a1 + 48);
        v22 = a1 + 448;
        strength = a1 + 436;
        v20 = a1 + 60;
        v14 = rf_receiver_get_first_dword((void *)a1);
        rf_weapon_spawn_impact_vclips(*(_DWORD *)(a1 + 664), v14, v20, strength, v22, v23);
      }
      if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(*(_DWORD *)(a1 + 660) + 612)) != 0 )
      {
        rf_gamesound_play_positional_event(
          *(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * *(_DWORD *)(a1 + 464) + 456),
          (float *)(a1 + 436),
          1.0,
          (int)flt_17F10B0,
          0);
      }
      else
      {
        v36 = rf_foley_choose_random_sound(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * *(_DWORD *)(a1 + 464) + 376));
        if ( (*(_DWORD *)(a1 + 680) & 8) != 0 )
        {
          name = rf_foley_definition_find_name("Riot Impact");
          v36 = rf_foley_choose_random_sound(name);
        }
        if ( rf_object_is_entity(v63) )
        {
          v35 = v63;
          if ( *(_DWORD *)(a1 + 664) == unk_911CB0 && rf_entity_class_has_contact_geomod_flag400(v35) )
          {
            v16 = rf_foley_definition_find_name("Screa Ram Sub");
            v36 = rf_foley_choose_random_sound(v16);
          }
        }
        if ( v36 == -1 )
          v36 = rf_foley_choose_random_sound(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 376));
        rf_gamesound_play_positional_event(v36, (float *)(a1 + 436), 1.0, (int)flt_17F10B0, 0);
      }
    }
    if ( byte_704E83 != 1 && *(_DWORD *)(a1 + 664) == rf_weapon_id_flamethrower && (*(_DWORD *)(a1 + 680) & 0x20) != 0 )
    {
      v23 = *(int *)(a1 + 48);
      v22 = a1 + 448;
      strength = a1 + 436;
      v20 = 0;
      v17 = rf_receiver_get_first_dword((void *)a1);
      rf_weapon_spawn_impact_vclips(*(_DWORD *)(a1 + 664), v17, v20, strength, v22, v23);
    }
    return v59;
  }
}

