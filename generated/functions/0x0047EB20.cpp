// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047EB20 rf_rfl_events_section_load
// UNREALRED VERIFIED [mission-play-animation-file-20261013] Play_Animation serialization has two branches: at0x47EEF5 a nonempty SECOND string selects internal event type12 through0x4FA1B0, passing bool0 as hold and bool1 as action selector. Only an empty second string uses canonical first-string type11 through0x4FA0F0. Filename precedence is unconditional. All48 Play_Animation records in the33 independently captured event sections have first string none and a nonempty filename in second string;34 distinct filenames.
// UNREALRED VERIFIED [mission-mover-events-20261020] Specialized mover field routing verified: type89 passes integer0==0 to0x4FA9D0; type66 passes string0 and float0 to0x4FAF00; type72 calls0x4FAFF0 with no extra fields. Shared authored delay and target list remain populated by the common loader.
// UNREALRED VERIFIED [mission-protection-20261020] Type24 passes generic first float v45 to0x4FAA00 as protection duration. Serialized ScriptName becomes the event/common name used for the special case-insensitive player target, independently of the two raw string parameters. Type50 builds its separate pending visibility owner through0x4FAEB0.
void __cdecl rf_rfl_events_section_load(_DWORD *a1)
{
  char *v1; // eax
  char *v2; // eax
  char *v3; // eax
  char *v4; // eax
  char *v5; // eax
  char *v6; // eax
  char *v7; // eax
  char *v8; // eax
  int v9; // eax
  char *v10; // eax
  char *v11; // eax
  int *v12; // eax
  char *v13; // [esp-4h] [ebp-CCh]
  float v14; // [esp+0h] [ebp-C8h]
  float v15; // [esp+4h] [ebp-C4h] BYREF
  char *v16; // [esp+8h] [ebp-C0h]
  float v17; // [esp+Ch] [ebp-BCh]
  int v18; // [esp+14h] [ebp-B4h]
  int v19; // [esp+18h] [ebp-B0h]
  unsigned int v20; // [esp+1Ch] [ebp-ACh]
  float *v21; // [esp+20h] [ebp-A8h]
  int v22; // [esp+24h] [ebp-A4h] BYREF
  void *explode_record; // [esp+28h] [ebp-A0h]
  int v24; // [esp+2Ch] [ebp-9Ch]
  unsigned int v25; // [esp+30h] [ebp-98h]
  int v26; // [esp+34h] [ebp-94h]
  int j; // [esp+38h] [ebp-90h]
  unsigned __int8 v28; // [esp+3Fh] [ebp-89h]
  int v29; // [esp+40h] [ebp-88h] BYREF
  int slot_version; // [esp+44h] [ebp-84h]
  float v31; // [esp+48h] [ebp-80h]
  int v32; // [esp+4Ch] [ebp-7Ch]
  float v33[9]; // [esp+50h] [ebp-78h] BYREF
  int int32_versioned; // [esp+74h] [ebp-54h]
  int v35[2]; // [esp+78h] [ebp-50h] BYREF
  int v36[2]; // [esp+80h] [ebp-48h] BYREF
  int v37; // [esp+88h] [ebp-40h]
  int i; // [esp+8Ch] [ebp-3Ch]
  float float_versioned; // [esp+90h] [ebp-38h]
  unsigned __int8 bool_versioned; // [esp+97h] [ebp-31h]
  float v41[3]; // [esp+98h] [ebp-30h] BYREF
  int v42[2]; // [esp+A4h] [ebp-24h] BYREF
  int v43; // [esp+ACh] [ebp-1Ch]
  int v44[2]; // [esp+B0h] [ebp-18h] BYREF
  float v45; // [esp+B8h] [ebp-10h]
  int v46; // [esp+C4h] [ebp-4h]

  rf_string_construct_empty(v44);
  v46 = 0;
  rf_string_construct_empty(v35);
  LOBYTE(v46) = 1;
  rf_vector3_default_construct_noop(v41);
  rf_string_construct_empty(v36);
  LOBYTE(v46) = 2;
  rf_string_construct_empty(v42);
  LOBYTE(v46) = 3;
  rf_matrix3_construct((char *)v33);
  rf_rgba8_default_construct_noop(&v29);
  slot_version = rf_vfile_get_slot_version(a1);
  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  for ( i = 0; i < int32_versioned; ++i )
  {
    v32 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_string_object_versioned(a1, v35, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(a1, v41, 0, unk_1C8FBDC);
    rf_binary_stream_read_string_object_versioned(a1, v44, 0, nullptr);
    if ( slot_version < 61 )
      rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    float_versioned = rf_binary_stream_read_float_versioned(a1, 53, 0.0);
    bool_versioned = rf_binary_stream_read_bool_versioned(a1, 0, 1);
    v28 = rf_binary_stream_read_bool_versioned(a1, 100, 0);
    v43 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    v37 = rf_binary_stream_read_int32_versioned(a1, 58, 0);
    v45 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v31 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    rf_binary_stream_read_string_object_versioned(a1, v36, 0, nullptr);
    rf_binary_stream_read_string_object_versioned(a1, v42, 0, nullptr);
    v24 = -1;
    rf_pointer_array_release_storage((void **)unk_6FCCC8);
    v26 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    for ( j = 0; j < v26; ++j )
    {
      v24 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
      rf_pointer_array_append_dword(unk_6FCCC8, v24);
    }
    explode_record = nullptr;
    v25 = rf_mission_event_type_from_name((int)v35);
    if ( v25 == 4 || v25 == 63 || v25 == 70 )
      rf_binary_stream_read_matrix3_vectors_201_versioned((char *)v33, 145, (int)unk_1C8FC18);
    if ( v25 == 46 )
      rf_binary_stream_read_matrix3_vectors_201_versioned((char *)v33, 152, (int)unk_1C8FC18);
    v29 = *rf_binary_stream_read_packed4bytes_versioned(a1, &v22, 176, &dword_1C8FC4C);
    v20 = v25;
    switch ( v25 )
    {
      case 0u:
        v17 = *(float *)&v43;
        v16 = (char *)bool_versioned;
        v15 = v31;
        v14 = v45;
        v13 = (char *)rf_string_object_c_str_or_empty(v42);
        v1 = (char *)rf_string_object_c_str_or_empty(v36);
        explode_record = (void *)rf_event_sound_create_from_fields(
                                   (int)v41,
                                   v1,
                                   v13,
                                   v14,
                                   v15,
                                   (char)v16,
                                   SLODWORD(v17));
        break;
      case 1u:
        v2 = (char *)rf_string_object_c_str_or_empty(v36);
        explode_record = (void *)rf_event_slay_create_from_fields((int)v41, v2);
        break;
      case 5u:
        explode_record = rf_event_goto_build_from_generic_fields((int)v41, bool_versioned, v28, v43, v37);
        break;
      case 6u:
        explode_record = (void *)rf_event_goto_player_create_from_fields((int)v41, bool_versioned);
        break;
      case 7u:
        explode_record = (void *)rf_event_look_at_create_from_fields((int)v41, v43);
        break;
      case 9u:
        explode_record = (void *)rf_event_shoot_once_create_from_fields((int)v41, v43);
        break;
      case 0xAu:
        v3 = (char *)rf_string_object_c_str_or_empty(v36);
        explode_record = (void *)rf_event_create_explode_record((int)v41, bool_versioned, v45, v31, v3);
        break;
      case 0xBu:
        if ( (int)rf_string_length_from_cstr((const char **)v42) <= 0 )
        {
          explode_record = (void *)rf_event_play_animation_build_from_name(
                                     (int)v41,
                                     (std::exception *)v36,
                                     bool_versioned);
        }
        else
        {
          explode_record = (void *)rf_play_animation_file_event_create((int)v41, (int)v42, bool_versioned, v28);
          v25 = 12;
        }
        break;
      case 0xDu:
        explode_record = (void *)rf_event_heal_create_from_fields((int)v41, v43, bool_versioned);
        break;
      case 0xEu:
        explode_record = (void *)rf_event_shield_create_from_fields((int)v41, v43, bool_versioned);
        break;
      case 0xFu:
        explode_record = (void *)rf_event_message_build_from_generic_fields(
                                   (int)v41,
                                   v43,
                                   (int)v45,
                                   bool_versioned,
                                   v37);
        break;
      case 0x10u:
        explode_record = (void *)rf_event_when_dead_create((int)v41, bool_versioned);
        break;
      case 0x11u:
        explode_record = (void *)rf_event_continuous_damage_create_from_fields((int)v41, v43, v37);
        break;
      case 0x12u:
        explode_record = (void *)rf_event_shake_player_create_from_fields((int)v41, v45, v31);
        break;
      case 0x13u:
        explode_record = (void *)rf_event_give_item_to_player_create_from_name((int)v41, (std::exception *)v36);
        break;
      case 0x14u:
        explode_record = (void *)rf_event_create_cyclic_timer_record((int)v41, v45, v43, bool_versioned);
        break;
      case 0x15u:
        explode_record = (void *)rf_event_create_switch_model_record((int)v41, (int)v36);
        break;
      case 0x16u:
        explode_record = (void *)rf_event_create_load_level_record((int)v41, (char **)v36, bool_versioned);
        break;
      case 0x17u:
        explode_record = (void *)rf_event_create_spawn_object_from_names(
                                   (int)v41,
                                   (int)v36,
                                   (std::exception *)v42,
                                   bool_versioned,
                                   v45);
        break;
      case 0x18u:
        explode_record = (void *)rf_event_make_invulnerable_build_from_duration((int)v41, v45);
        break;
      case 0x1Cu:
        LODWORD(v17) = v28;
        v16 = (char *)bool_versioned;
        v15 = COERCE_FLOAT(rf_string_object_c_str_or_empty(v42));
        v4 = (char *)rf_string_object_c_str_or_empty(v36);
        explode_record = (void *)rf_event_create_follow_waypoints_record(
                                   (int)v41,
                                   v4,
                                   (char *)LODWORD(v15),
                                   (char)v16,
                                   SLOBYTE(v17));
        break;
      case 0x1Eu:
        explode_record = (void *)rf_event_set_friendliness_create_from_fields((int)v41, v43);
        break;
      case 0x1Fu:
        explode_record = (void *)rf_event_set_light_state_create_from_fields((int)v41, v43);
        break;
      case 0x20u:
        LODWORD(v17) = bool_versioned;
        v16 = (char *)rf_string_object_c_str_or_empty(v36);
        explode_record = (void *)rf_event_create_switch_record((int)v41, v43, v37, (int)v45, v16, SLOBYTE(v17));
        break;
      case 0x21u:
        v17 = COERCE_FLOAT(rf_string_object_c_str_or_empty(v42));
        v16 = (char *)v37;
        v5 = (char *)rf_string_object_c_str_or_empty(v36);
        explode_record = rf_event_create_swap_textures_record((int)v41, v43, v5, (int)v16, (char *)LODWORD(v17));
        break;
      case 0x22u:
        explode_record = (void *)rf_event_set_ai_mode_build_from_option((int)v41, v43, 1);
        break;
      case 0x23u:
        v6 = (char *)rf_string_object_c_str_or_empty(v44);
        explode_record = (void *)rf_event_create_goal_record((int)v41, v37, bool_versioned, v6);
        break;
      case 0x24u:
        explode_record = (void *)rf_event_create_goal_check_record((int)v41, (int)v36, v43);
        break;
      case 0x25u:
        explode_record = (void *)rf_event_create_goal_set_record((int)v41, (int)v36);
        break;
      case 0x26u:
        explode_record = (void *)rf_event_attack_create_from_fields((int)v41, v43);
        break;
      case 0x28u:
        explode_record = (void *)rf_event_set_liquid_depth_create_from_fields((int)v41, v45, v31);
        break;
      case 0x29u:
        LODWORD(v17) = v28;
        v7 = (char *)rf_string_object_c_str_or_empty(v36);
        explode_record = (void *)rf_event_music_start_create_from_fields((int)v41, v7, SLOBYTE(v17));
        break;
      case 0x2Au:
        explode_record = (void *)rf_event_music_stop_create_from_fields((int)v41, v45);
        break;
      case 0x2Cu:
        explode_record = (void *)rf_event_set_gravity_create_from_fields((int)v41, v45);
        break;
      case 0x2Du:
        explode_record = (void *)rf_event_alarm_siren_create_from_fields((int)v41);
        break;
      case 0x2Eu:
        explode_record = (void *)rf_event_alarm_create_from_fields((int)v41);
        break;
      case 0x2Fu:
        explode_record = (void *)rf_event_go_undercover_create_from_fields((int)v41, v43);
        break;
      case 0x31u:
        explode_record = (void *)rf_event_monitor_state_create_from_fields((int)v41, v43, bool_versioned, v45);
        break;
      case 0x32u:
        explode_record = (void *)rf_event_unhide_create((int)v41);
        break;
      case 0x39u:
        explode_record = (void *)rf_event_fog_state_create_from_fields((int)v41);
        break;
      case 0x3Au:
        explode_record = (void *)rf_event_detach_create_from_fields((int)v41);
        break;
      case 0x3Bu:
        v17 = v45;
        v8 = (char *)rf_string_object_c_str_or_empty(v36);
        explode_record = (void *)rf_event_skybox_state_create((int)v41, v8, v17);
        break;
      case 0x3Du:
        explode_record = (void *)rf_event_create_blackout_player_record((int)v41, bool_versioned, v28, v45);
        break;
      case 0x42u:
        v17 = v45;
        v21 = &v15;
        rf_string_copy_construct_from_object(&v15, (char **)v36);
        v19 = v9;
        v18 = rf_event_modify_rotating_mover_build_from_fields((int)v41, SLODWORD(v15), (int)v16, v17);
        explode_record = (void *)v18;
        break;
      case 0x45u:
        explode_record = (void *)rf_event_enable_nav_point_create_from_fields((int)v41);
        break;
      case 0x46u:
        v17 = v45;
        v10 = (char *)rf_string_object_c_str_or_empty(v36);
        explode_record = (void *)rf_event_create_play_vclip_record((int)v41, v10, v17);
        break;
      case 0x47u:
        explode_record = (void *)rf_event_endgame_create_from_fields((int)v41);
        break;
      case 0x48u:
        explode_record = (void *)rf_event_mover_pause_create((int)v41);
        break;
      case 0x49u:
        explode_record = (void *)rf_event_countdown_begin_create_from_fields((int)v41, v43);
        break;
      case 0x54u:
        explode_record = (void *)rf_event_create_when_countdown_reaches_record((int)v41, v43);
        break;
      case 0x55u:
        v11 = (char *)rf_string_object_c_str_or_empty(v36);
        explode_record = (void *)rf_event_create_fullscreen_image_record((int)v41, v11);
        break;
      case 0x57u:
        explode_record = (void *)rf_event_create_when_life_reaches_record((int)v41, v43);
        break;
      case 0x58u:
        explode_record = (void *)rf_event_create_when_armor_reaches_record((int)v41, v43);
        break;
      case 0x59u:
        explode_record = (void *)rf_event_reverse_mover_build_from_direction((int)v41, v43 == 0);
        break;
      default:
        explode_record = (void *)rf_mission_event_create_at_position((int)v41, v25);
        break;
    }
    if ( explode_record )
    {
      *((_DWORD *)explode_record + 164) = v25;
      *((float *)explode_record + 165) = float_versioned;
      *((_DWORD *)explode_record + 9) = v32;
      rf_string_assign_from_object((_DWORD *)explode_record + 7, (int)v44);
      rf_matrix3_copy((float *)explode_record + 19, v33);
      for ( j = 0; j < v26; ++j )
      {
        v12 = (int *)sub_552200(unk_6FCCC8, j);
        rf_pointer_array_append_dword((_DWORD *)explode_record + 167, *v12);
      }
    }
  }
  LOBYTE(v46) = 2;
  rf_string_destroy_buffer(v42);
  LOBYTE(v46) = 1;
  rf_string_destroy_buffer(v36);
  LOBYTE(v46) = 0;
  rf_string_destroy_buffer(v35);
  v46 = -1;
  rf_string_destroy_buffer(v44);
}

