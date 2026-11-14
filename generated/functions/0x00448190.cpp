// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448190 sub_448190
// UNREALRED VERIFIED [combat-native-pickup-runtime-20261111]: Level Initializing wrapper calls4EF150 ONLY if incoming restore/continuation bytea1==0. That resets alarm/undercover ACTIVE bytes only, leaving session voice/deadline. Keep source lease rotation/new level admission separate from resource retirement and raw clock-domain preservation; no reset on pickup rebuild or GeoMod publication.
void __cdecl sub_448190(char a1)
{
  char *v1; // eax
  int v2; // eax
  int v3[2]; // [esp-Ch] [ebp-38h] BYREF
  int v4; // [esp-4h] [ebp-30h] BYREF
  char *v5; // [esp+0h] [ebp-2Ch]
  int v6; // [esp+8h] [ebp-24h]
  _DWORD *v7; // [esp+Ch] [ebp-20h]
  _DWORD *v8; // [esp+10h] [ebp-1Ch]
  int v9; // [esp+14h] [ebp-18h]
  int *v10; // [esp+18h] [ebp-14h]
  void *v11; // [esp+1Ch] [ebp-10h]
  int v12; // [esp+28h] [ebp-4h]

  if ( !unk_6EDD3D )
    rf_game_initialization_notice_and_clear_level_cache();
  rf_console_output_append_text_lines("-- Level Initializing --\n", nullptr);
  rf_liquid_room_transitions_clear();
  rf_progress_update_poll_network_and_callback(0, 0);
  rf_ambient_sound_level_reset();
  rf_object_delete_unprotected_slots_and_reset_counter();
  rf_progress_update_poll_network_and_callback(0, 0);
  rf_weapon_count_empty_iteration();
  rf_entity_reset_local_impact_state_and_cache_helmet_audio();
  rf_physics_set_gravity_acceleration(9.8000002);
  rf_progress_update_poll_network_and_callback(0, 0);
  sub_473020();
  sub_504340();
  rf_ai_global_deadlines_initialize();
  rf_progress_update_poll_network_and_callback(0, 0);
  sub_486E80();
  rf_hud_reset_layers_unless_flag704E83_is1();
  rf_geomod_network_history_level_init();
  rf_geomod_execution_queue_level_init();
  rf_vclip_effect_pool_clear_runtime();
  rf_hook_4182B0_noop();
  rf_renderer_reset_light_records_when_enabled();
  rf_scene_point_pool_mark_all_unused();
  rf_geomod_operation_runtime_level_init();
  rf_mission_event_registry_clear();
  rf_hook_41D2C0_noop();
  rf_progress_update_poll_network_and_callback(0, 0);
  rf_volume_system_clear();
  rf_procedural_bitmap_pool_clear();
  rf_mover_reset_sequence_and_free_aux_ring();
  rf_monitor_reset_global_dword_6807E0();
  rf_geomod_impact_chunks_initialize80();
  rf_cutscene_level_reset();
  rf_local_players_clear_224_and_reset_weapon_models();
  rf_extras_panel_noop_hook();
  rf_camera_reset_sample_arrays();
  rf_clutter_reset_counter_and_allocated_bitset();
  rf_progress_update_poll_network_and_callback(0, 0);
  rf_firing_effect_ring_destroy_all();
  sub_43E8A0();
  rf_rail_trail_reset_pool16();
  rf_projected_shadows_initialize();
  rf_room_reset_descending_id_counter();
  rf_explosion_graph_pool_initialize();
  if ( !a1 )
  {
    rf_local_players_reset_level_runtime_state();
    rf_undercover_initialize_runtime_state();
    rf_goal_reset_shared_record_count();
    rf_hud_message_noop_callback_44B220();
  }
  if ( rf_multiplayer_runtime_mode )
    sub_48EF50();
  if ( rf_splitscreen_runtime_active || unk_7B25D1 )
    rf_splitscreen_reset_respawn_and_shared_state();
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    v5 = (char *)dword_6FC3A8;
    v1 = (char *)rf_string_object_c_str_or_empty(unk_6FC3AC);
    v9 = rf_vfile_compare_raw_crc32(v1, (int)v5);
    if ( v9 == -1 )
    {
      rf_client_leave_game_notify_and_exit(*(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20), 7);
    }
    else if ( v9 )
    {
      if ( v9 == 1 )
        rf_client_leave_game_notify_and_exit(*(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20), 4);
    }
    else
    {
      v11 = &v4;
      v8 = rf_string_construct_from_cstr(&v4, (char *)&byte_633CAD);
      v7 = v8;
      v12 = 0;
      v10 = v3;
      rf_string_copy_construct_from_object(v3, (char **)unk_6FC3AC);
      v6 = v2;
      v12 = -1;
      rf_level_transition_assign_level_and_save_strings(v3[0], (char *)v3[1], v4, v5);
    }
  }
  rf_ai_resume_updates();
  unk_6EDD38 = 0;
}

