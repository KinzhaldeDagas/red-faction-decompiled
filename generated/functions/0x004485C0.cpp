// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004485C0 sub_4485C0
// UNREALRED VERIFIED [combat-native-pickup-source-20261111] Level-start postload remaps Entity+0x76C (AI+0x4CC): if raw value!=-1, lookup saved UID via mission-event saved-UID registry; only a found event overwrites it with enclosing Event+0x30 full runtime handle. A miss retains the original signed value, not -1. Later40AEB0 uses4F76D0 full-handle lookup. Unreal must preserve authored identity versus finalized reference and cannot infer all missing positive authored IDs are null runtime handles. Fresh19/20 original asm:4487B1..4487DE.
void **__cdecl sub_4485C0(char a1)
{
  const char *v1; // eax
  float *v2; // eax
  void *v3; // ecx
  float copy_result[3]; // [esp+18h] [ebp-40h] BYREF
  float sum_result[3]; // [esp+24h] [ebp-34h] BYREF
  int saved_uid_for_death; // [esp+30h] [ebp-28h]
  int v8; // [esp+34h] [ebp-24h]
  char v9; // [esp+3Bh] [ebp-1Dh]
  int level_record_by_name; // [esp+3Ch] [ebp-1Ch]
  void *i; // [esp+40h] [ebp-18h]
  float destination[3]; // [esp+44h] [ebp-14h] BYREF
  int j; // [esp+50h] [ebp-8h]
  int *k; // [esp+54h] [ebp-4h]

  i = nullptr;
  rf_vector3_default_construct_noop(destination);
  if ( a1 && unk_6FC3B4 )
  {
    if ( dword_681E38 )
    {
      rf_object_relocate_reset_pose_and_reactivate((void *)dword_681E38, &flt_6FC434, (float *)unk_6FC440);
      rf_object_set_room_and_cache_position((float *)dword_681E38, 0);
    }
  }
  else if ( a1 && (int)rf_string_length_from_cstr((const char **)unk_6FC478) > 0 )
  {
    level_record_by_name = rf_goal_find_level_record_by_name((int)unk_6FC478);
    if ( !level_record_by_name )
    {
      v1 = rf_string_object_c_str_or_empty(unk_6FC478);
      sprintf(&unk_18CD828, "Cannot find event marker named: %s", v1);
      rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\gamesrc\\gamewide\\gamewide.cpp", 1549, &unk_18CD828);
    }
    for ( i = (void *)unk_7D0C90; i != &unk_7D0C80; i = *((void **)i + 4) )
    {
      if ( (*((_DWORD *)i + 31) & 0x800) != 0 )
      {
        v2 = rf_vector_add((const float *)i + 160, sum_result, (const float *)(level_record_by_name + 64));
        rf_vector_copy(destination, copy_result, v2);
        rf_object_relocate_reset_pose_and_reactivate(i, destination, (float *)i + 18);
      }
    }
    rf_world_decal_translate_and_rebind_preserved(rf_world_solid, (float *)(level_record_by_name + 64));
    rf_string_assign_from_cstr(unk_6FC478, (char *)&byte_633CAE);
  }
  else
  {
    for ( i = (void *)unk_7D0C90; i != &unk_7D0C80; i = *((void **)i + 4) )
      rf_object_set_room_and_cache_position((float *)i, 0);
  }
  for ( j = unk_68211C; (_UNKNOWN *)j != &unk_681E90; j = *(_DWORD *)(j + 652) )
  {
    if ( (*(_DWORD *)(j + 124) & 2) == 0 )
    {
      if ( *(_DWORD *)(j + 1896) != -1 )
      {
        v8 = rf_object_find_by_saved_identifier(*(_DWORD *)(j + 1896));
        if ( v8 )
          *(_DWORD *)(j + 1896) = *(_DWORD *)(v8 + 44);
      }
      if ( *(_DWORD *)(j + 1900) != -1 )
      {
        saved_uid_for_death = rf_mission_event_registry_find_saved_uid_for_death(*(_DWORD *)(j + 1900));
        if ( saved_uid_for_death )
          *(_DWORD *)(j + 1900) = *(_DWORD *)(saved_uid_for_death + 48);
      }
      if ( *(_DWORD *)(j + 1872) != -1 )
        rf_ai_restore_saved_parent_slot((int *)(j + 672));
      v9 = 1;
      if ( rf_entity_descriptor_mode_is_12_15_13_11_or9(j) || rf_entity_movement_is_index4_or7(j) )
        v9 = 0;
      if ( (*(_DWORD *)(j + 2068) & 0x4000) == 0 )
        sub_40FD80(
          (float *)(j + 60),
          *(float *)(j + 1984),
          *(float *)(j + 1988),
          v9,
          (int *)(j + 1692),
          (int *)(j + 1696),
          0);
    }
  }
  rf_world_allocate_model_instance_render_data();
  rf_world_build_model_instance_rgb_packets();
  rf_level_preload_render_and_effect_resources();
  if ( a1 )
    rf_player_level_setup_hook_noop();
  rf_weapon_preload_all_player_weapon_impact_vclips();
  rf_ambient_sounds_initialize_frontend_slots();
  rf_underwater_particles_initialize();
  rf_glass_shard_system_init();
  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
  {
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      sub_4B0E40();
    if ( unk_7B25D1 )
      rf_ui_request_panel_immediate(18, 0);
    else
      rf_ui_request_panel_immediate(11, 0);
  }
  else
  {
    rf_ui_request_panel_immediate(33, 0);
  }
  if ( rf_game_pause_gate_query() )
    rf_game_unpause_unless_locked(1);
  rf_progress_update_poll_network_and_callback(0, 0);
  sub_501FF0();
  rf_progress_update_poll_network_and_callback(0, 0);
  for ( k = (int *)dword_6807E4; k != &dword_6807E4; k = (int *)*k )
  {
    rf_monitor_render_selected_entity_view(k);
    v3 = (void *)*k;
  }
  rf_level_finalize_trigger_and_mover_links(v3);
  rf_camera_initialize_occupied_slots();
  if ( unk_7B25D1 )
    rf_splitscreen_match_initialize();
  rf_level_build_clutter_hud_registries();
  if ( dword_681E38 && !rf_splitscreen_runtime_active )
    rf_entity_apply_named_skin_profile(dword_681E38, "parker");
  return rf_console_execute_script_file("levelstart.vcs");
}

