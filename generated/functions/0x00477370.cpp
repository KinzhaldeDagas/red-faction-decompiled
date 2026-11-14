// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00477370 rf_level_load_and_initialize_world
// UNREALRED VERIFIED [trigger-airlock-20261022] Level world setup invokes515FD0 across loaded rooms after parsing, deriving initial mutable room pressure from portal topology before airlock queries.
// UNREALRED VERIFIED [local-multiplayer-20261028] Initial player creation occurs only after successful RFL load and when no current local gameplay entity exists. In multiplayer only server authority enters this host path; it selects a decoded multiplayer respawn transform, then creates the local entity with the selected multiplayer character. Remote clients obtain entities through the authoritative creation packet path rather than independently creating a host pawn.
// UNREALRED VERIFIED [cutscene-playback-20261028]: Stops owned music, runs renderer/sound/file preparation, substitutes default level0x6FC308 for empty requested level, resets level render globals and sky rotation speed, ends cutscene, pauses sound/stops voice slots, calls0x485650 then rf_rfl_level_load(level,second string,output buffer). Failure invokes teardown0x477770 and returns-1. Success arms manual respawn gate0ms, rebuilds liquid surfaces and pressure topology for every room, records authored-sky presence. Creates local entity only if non-MP or server, no current entity, global0x704E83!=1, panels not9/10 and0x7B25D1 clear; SP uses authored transform, MP server selects respawn point and multiplayer character. Runs0x526300 and sets level flags0x6FC424=1; optional precomputed intro predicate feeds copied0x6FC464 text to0x58E020. Returns0. Input RF strings can be modified on default
// substitution; no source/type changes applied.
int __cdecl rf_level_load_and_initialize_world(std::exception *a1, std::exception *a2, char *Buffer)
{
  char *v3; // eax
  char *v4; // eax
  char *v6; // [esp-8h] [ebp-F8h]
  char v7; // [esp+3h] [ebp-EDh]
  char *v8; // [esp+8h] [ebp-E8h]
  const char *v9; // [esp+Ch] [ebp-E4h]
  float copy_result[3]; // [esp+10h] [ebp-E0h] BYREF
  char v11[4]; // [esp+1Ch] [ebp-D4h] BYREF
  char String2[132]; // [esp+20h] [ebp-D0h] BYREF
  float destination[3]; // [esp+A8h] [ebp-48h] BYREF
  float v14[9]; // [esp+B4h] [ebp-3Ch] BYREF
  _BYTE *v15; // [esp+D8h] [ebp-18h]
  int i; // [esp+DCh] [ebp-14h]
  bool v17; // [esp+E3h] [ebp-Dh]
  int v18; // [esp+E4h] [ebp-Ch]
  int first_dword; // [esp+E8h] [ebp-8h]
  int j; // [esp+ECh] [ebp-4h]

  v18 = rf_ui_panel_stack_current_id();
  v17 = !rf_rf_string_not_equals_cstring_case_insensitive((int)a1, "l1s1.rfl");
  if ( !rf_string_is_empty((int *)a2) )
    v17 = 0;
  if ( v18 == 10 && rf_rf_string_not_equals_cstring_case_insensitive((int)unk_6FC31C, "train02.rfl") )
    v17 = 0;
  rf_music_owned_stop();
  rf_sound_backend_service_fades_adapter();
  rf_sound_frontend_update();
  rf_bitmap_begin_residency_scope_unless_suppressed();
  if ( rf_string_is_empty((int *)a1) )
  {
    rf_string_assign_from_object(a1, (int)dword_6FC308);
    rf_string_assign_from_cstr(a2, (char *)&byte_63853B);
  }
  rf_audio_environment_restore_saved_room_level();
  unk_6FC344 = *(_DWORD *)rf_rgba8_construct_components_return_self(v11, 100, 100, 100, 255);
  unk_6FC348 = 0.0;
  unk_6FC34C = 100.0;
  unk_6FC350 = 100.0;
  unk_6FC354 = 0;
  rf_skybox_rotation_axis = 120;
  rf_skybox_rotation_degrees_per_second = 0.0;
  rf_main_menu_restart_music_pending = 1;
  if ( rf_multiplayer_runtime_mode == 1 )
  {
    unk_78C248 = 0;
    for ( i = 0; i < 200; ++i )
      dword_78BF28[i] = -1;
  }
  rf_cutscene_end_restore_player_state();
  rf_music_owned_stop();
  rf_sound_backend_set_paused(1);
  rf_gamesound_stop_all_voice_slots();
  v3 = (char *)rf_string_object_c_str_or_empty(a1);
  rf_level_text_load_for_level(v3);
  v6 = (char *)rf_string_object_c_str_or_empty(a2);
  v4 = (char *)rf_string_object_c_str_or_empty(a1);
  if ( rf_rfl_level_load(v4, v6, Buffer) >= 0 )
  {
    rf_replicator_arm_milliseconds(&rf_manual_respawn_gate_event, 0);
    first_dword = rf_receiver_get_first_dword((void *)(rf_world_solid + 156));
    unk_6FC355 = 0;
    for ( j = 0; j < first_dword; ++j )
    {
      v15 = *(_BYTE **)sub_552200((_DWORD *)(rf_world_solid + 156), j);
      rf_liquid_room_surface_rebuild((int)v15, rf_world_solid);
      sub_515FD0((int)v15);
      if ( rf_room_is_authored_sky(v15) )
        unk_6FC355 = 1;
    }
    if ( (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority) && !dword_681E38 && byte_704E83 != 1 )
    {
      rf_vector3_default_construct_noop(destination);
      rf_matrix3_construct((char *)v14);
      if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      {
        rf_respawn_point_select((int)destination, (int)v14, rf_local_fpgun_player);
      }
      else
      {
        rf_vector_copy(destination, copy_result, &flt_6FC434);
        rf_matrix3_copy(v14, (const float *)unk_6FC440);
      }
      if ( v18 != 10 && v18 != 9 && !unk_7B25D1 )
      {
        if ( rf_multiplayer_runtime_mode == 1 )
          rf_multiplayer_player_entity_create(
            rf_local_fpgun_player,
            *(_DWORD *)(rf_local_fpgun_player + 24),
            (int)destination,
            (int)v14,
            *(_DWORD *)(rf_local_fpgun_player + 3932));
        else
          rf_multiplayer_player_entity_create(
            rf_local_fpgun_player,
            *(_DWORD *)(rf_local_fpgun_player + 24),
            (int)destination,
            (int)v14,
            -1);
      }
    }
    rf_geometry_set_current_context(rf_world_solid, (int)&unk_704600);
    unk_6FC424 = 1;
    if ( v17 )
    {
      v9 = rf_string_object_c_str_or_empty(dword_6FC464);
      v8 = String2;
      do
      {
        v7 = *v9;
        *v8++ = *v9++;
      }
      while ( v7 );
      rf_movie_play_bink_blocking(String2);
    }
    return 0;
  }
  else
  {
    rf_level_destroy_runtime_resources();
    return -1;
  }
}

