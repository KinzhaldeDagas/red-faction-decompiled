// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050B590 rf_projectile_world_contact_response
// UNREALRED VERIFIED [weapon-impact-decode]: Handles ordinary projectile contact with static world geometry.
char __cdecl rf_projectile_world_contact_response(int a1)
{
  float *v2; // eax
  int first_dword; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  char *v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // [esp+10h] [ebp-F4h]
  int scalar; // [esp+18h] [ebp-ECh]
  float v13[3]; // [esp+1Ch] [ebp-E8h] BYREF
  float copy_result[3]; // [esp+28h] [ebp-DCh] BYREF
  float out_vector[3]; // [esp+34h] [ebp-D0h] BYREF
  int v16[3]; // [esp+40h] [ebp-C4h] BYREF
  float v17[3]; // [esp+4Ch] [ebp-B8h] BYREF
  float v18[3]; // [esp+58h] [ebp-ACh] BYREF
  float scaled_result[3]; // [esp+64h] [ebp-A0h] BYREF
  float selected_damage_with_owner_scale; // [esp+70h] [ebp-94h]
  char v21; // [esp+76h] [ebp-8Eh]
  char v22; // [esp+77h] [ebp-8Dh]
  int v23; // [esp+78h] [ebp-8Ch]
  int v24; // [esp+7Ch] [ebp-88h]
  float v25[3]; // [esp+80h] [ebp-84h] BYREF
  int v26; // [esp+8Ch] [ebp-78h]
  float sum_result[3]; // [esp+90h] [ebp-74h] BYREF
  float v28; // [esp+9Ch] [ebp-68h]
  int v29; // [esp+A0h] [ebp-64h]
  int v30; // [esp+A4h] [ebp-60h]
  char v31; // [esp+ABh] [ebp-59h]
  float position[3]; // [esp+ACh] [ebp-58h] BYREF
  float normal[16]; // [esp+B8h] [ebp-4Ch] BYREF
  char v34; // [esp+FAh] [ebp-Ah] BYREF
  char v35; // [esp+FBh] [ebp-9h] BYREF
  _DWORD *v36; // [esp+FCh] [ebp-8h]
  bool v37; // [esp+103h] [ebp-1h]

  v30 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 48));
  v36 = sub_4DD720(*(_DWORD *)(a1 + 48));
  if ( v30 && v36 && rf_weapon_is_riot_stick(*(_DWORD *)(v30 + 676)) && rf_fpgun_state_is_resident((int)v36, 2) )
    return 0;
  v31 = 0;
  v29 = *(_DWORD *)(a1 + 496);
  v37 = ((unsigned int)&unk_1000000 & *(_DWORD *)(*(_DWORD *)(a1 + 660) + 612)) != 0;
  if ( !rf_geomod_face_owner_type1_flag152_clear(v29) || v37 )
  {
    rf_physics_hit_record_construct_noop((char *)position);
    if ( rf_projectile_trace_contact_continue(a1, (float *)(a1 + 436), &v34, &v35, position) )
    {
      if ( !v35 && !v34 )
      {
        if ( (*(_DWORD *)(*(_DWORD *)(a1 + 496) + 40) & 0x800) != 0 )
        {
          rf_vector_multiply_scalar((const float *)(a1 + 276), v25, -1.0);
          rf_vector_accumulate(v25, (float *)(a1 + 448));
          rf_vector3_scale_in_place_return_self(v25, 0.5);
          first_dword = rf_receiver_get_first_dword((void *)a1);
          rf_managed_particle_effect_list_add(
            (int **)flt_6FC400,
            first_dword,
            (float *)(a1 + 436),
            v25,
            "pipesteam",
            "steam");
        }
        v11 = LODWORD(normal[9]);
        v4 = rf_vector3_set_components_return_destination(v18, 0.0, 0.0, 0.0);
        rf_weapon_create_impact_decal(*(_DWORD *)(a1 + 664), position, v4, normal, v11, 0, 0);
      }
      if ( byte_704E83 != 1 )
        rf_weapon_present_world_impact((_DWORD *)a1, v35, 1);
      if ( !v34 )
        return 1;
    }
    else if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(*(_DWORD *)(a1 + 660) + 612)) != 0 )
    {
      v24 = rf_object_resolve_handle(*(_DWORD *)(a1 + 484));
      if ( !v24 || rf_vector3_is_exact_zero((float *)(a1 + 472)) )
      {
        v5 = rf_vector_negate((float *)(a1 + 448), v17);
        rf_orientation_from_forward_and_up_hint((float *)(a1 + 288), v5, (float *)(a1 + 264));
        v6 = rf_vector_scale((float *)v16, 0.050000001, (float *)(a1 + 312));
        v7 = rf_vector_subtract((const float *)(a1 + 436), out_vector, v6);
        rf_vector_copy((float *)(a1 + 240), copy_result, v7);
        rf_vector_copy((float *)(a1 + 60), v13, (const float *)(a1 + 240));
        rf_matrix3_copy((float *)(a1 + 72), (const float *)(a1 + 288));
        *(float *)(a1 + 432) = 0.0;
        v23 = *(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * *(_DWORD *)(a1 + 464) + 456);
        if ( v23 == -1 )
          v23 = *(_DWORD *)(*(_DWORD *)(a1 + 660) + 456);
        rf_gamesound_play_positional_event(v23, (float *)(a1 + 60), 1.0, (int)flt_17F10B0, 0);
        if ( (int)rf_string_length_from_cstr((const char **)(*(_DWORD *)(a1 + 660) + 28)) > 0 )
        {
          rf_object_release_owned_model_handle(a1);
          v8 = (char *)rf_string_object_c_str_or_empty((const void *)(*(_DWORD *)(a1 + 660) + 28));
          rf_object_bind_model_filename_by_kind(a1, v8, 3);
          rf_vfx_start_instance(*(int **)(a1 + 128), 0, 1.0, 1);
        }
        rf_vector3_zero_return_destination((float *)(a1 + 324));
        rf_physics_state_deactivate(a1 + 136);
        *(_DWORD *)(a1 + 424) &= ~8u;
      }
      return 1;
    }
    else if ( *(_DWORD *)(a1 + 664) == rf_weapon_index_grenade )
    {
      if ( (*(_DWORD *)(a1 + 680) & 0x10) != 0 )
        *(float *)(a1 + 52) = -1.0;
      else
        rf_weapon_present_world_impact((_DWORD *)a1, 0, 0);
      return 1;
    }
    else
    {
      v9 = rf_receiver_get_first_dword((void *)a1);
      v22 = rf_geomod_operation_admit(
              *(float *)(*(_DWORD *)(a1 + 660) + 332),
              *(_DWORD *)(a1 + 44),
              v9,
              (float *)(a1 + 436),
              (float *)(a1 + 448),
              0,
              0);
      if ( v22 == 1 )
      {
        rf_trigger_weapon_point_scan_all((float *)(a1 + 60));
        rf_projectile_apply_nearby_local_view_impulse(a1);
      }
      if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
      {
        v21 = (*(_DWORD *)(a1 + 680) & 0x20) != 0;
        selected_damage_with_owner_scale = rf_projectile_get_selected_damage_with_owner_scale(a1, v21);
        rf_damage_apply_radial(
          (float *)(a1 + 436),
          selected_damage_with_owner_scale,
          *(float *)(*(_DWORD *)(a1 + 660) + 520),
          *(_DWORD *)(a1 + 48),
          4 - (rf_weapon_id_flamethrower != *(_DWORD *)(a1 + 664)));
      }
      if ( byte_704E83 != 1 )
      {
        if ( v22 == 1 )
        {
          scalar = *(_DWORD *)(a1 + 48);
          v10 = rf_receiver_get_first_dword((void *)a1);
          rf_weapon_spawn_impact_vclips(*(_DWORD *)(a1 + 664), v10, a1 + 60, a1 - 76, a1 + 448, scalar);
        }
        else
        {
          rf_weapon_present_world_impact((_DWORD *)a1, 0, 1);
        }
      }
    }
    return v31;
  }
  else
  {
    v26 = *(_DWORD *)(v29 + 68);
    v31 = 1;
    v2 = rf_vector_multiply_scalar((const float *)(a1 + 276), scaled_result, 0.1);
    rf_vector_add((const float *)(a1 + 228), sum_result, v2);
    rf_object_publish_position_and_bounds(a1, sum_result);
    if ( byte_704E83 != 1 )
      rf_weapon_present_world_impact((_DWORD *)a1, 0, 1);
    v28 = *(float *)(*(_DWORD *)(a1 + 660) + 264);
    if ( sub_5119F0(*(_DWORD *)(a1 + 664)) || rf_weapon_has_flame_flag(*(_DWORD *)(a1 + 664)) )
      v28 = 1000.0;
    if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x40) == 0 )
    {
      *(float *)(v26 + 148) = *(float *)(v26 + 148) - v28;
      if ( *(float *)(v26 + 148) <= 0.0 )
        rf_room_try_break_first_glass_face(v26, (float *)(a1 + 436), (float *)(a1 + 96), 0);
    }
    return 1;
  }
}

