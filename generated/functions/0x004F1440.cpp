// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F1440 sub_4F1440
// UNREALRED VERIFIED [combat-speech-providers-20261111]: Startup calls446820 base+Foley registry before440A40 personas at4F17D9 and423520 entity classes at4F17FD. Persona references therefore resolve against ordered Foley slots, entity $Persona against initialized persona slots. No faction/class-name inference substitutes these registries.
int sub_4F1440()
{
  int physical_screen_width; // eax
  int v1; // eax
  int v2; // eax
  void *v3; // ecx
  int physical_screen_height; // [esp-20h] [ebp-2ACh]
  int v6; // [esp-20h] [ebp-2ACh]
  int v7; // [esp-20h] [ebp-2ACh]
  int v8; // [esp-14h] [ebp-2A0h]
  int v9; // [esp-14h] [ebp-2A0h]
  int v10; // [esp-14h] [ebp-2A0h]
  int v11[2]; // [esp-10h] [ebp-29Ch] BYREF
  int v12; // [esp-8h] [ebp-294h] BYREF
  char *v13; // [esp-4h] [ebp-290h]
  int v14; // [esp+4h] [ebp-288h]
  unsigned __int8 *v15; // [esp+Ch] [ebp-280h]
  char *v16; // [esp+10h] [ebp-27Ch]
  char *v17; // [esp+14h] [ebp-278h]
  _DWORD *v18; // [esp+18h] [ebp-274h]
  _DWORD *v19; // [esp+1Ch] [ebp-270h]
  _DWORD *v20; // [esp+20h] [ebp-26Ch]
  char v21; // [esp+27h] [ebp-265h]
  char *v22; // [esp+28h] [ebp-264h]
  char *v23; // [esp+2Ch] [ebp-260h]
  const char *argument; // [esp+30h] [ebp-25Ch]
  int *v25; // [esp+34h] [ebp-258h]
  void *v26; // [esp+38h] [ebp-254h]
  int v27; // [esp+3Ch] [ebp-250h]
  __time64_t Time; // [esp+40h] [ebp-24Ch] BYREF
  BOOL v29; // [esp+48h] [ebp-244h]
  int v30; // [esp+4Ch] [ebp-240h]
  int v32; // [esp+54h] [ebp-238h]
  int v33; // [esp+58h] [ebp-234h]
  int v34; // [esp+5Ch] [ebp-230h]
  char Str[512]; // [esp+60h] [ebp-22Ch] BYREF
  char *Source; // [esp+264h] [ebp-28h]
  char *last_char_wrapper; // [esp+268h] [ebp-24h]
  int v38; // [esp+26Ch] [ebp-20h]
  _DWORD v39[2]; // [esp+270h] [ebp-1Ch] BYREF
  char *v40; // [esp+278h] [ebp-14h]
  int level_extent; // [esp+27Ch] [ebp-10h] BYREF
  int v42; // [esp+288h] [ebp-4h]

  if ( !rf_command_line_bool_option_is_enabled(byte_88E45C) )
    rf_movie_play_bink_blocking("thqlogo.bik");
  unk_88E410 = rf_performance_clock_elapsed_scaled(1000);
  dword_663058 = rf_bitmap_load_with_optional_mipmap_generation("loadinglegal.tga", (void *)0xFFFFFFFF, 1);
  if ( dword_663058 >= 0 )
  {
    rf_bitmap_get_resolved_dimensions(dword_663058, v39, &level_extent);
    rf_render_color_set_rgba8(255, 255, 255, 255);
    rf_renderer_reset_viewport_full_screen();
    rf_renderer_clear_color_backend_dispatch();
    v13 = (char *)unk_187CD38;
    v11[0] = level_extent;
    v8 = v39[0];
    physical_screen_height = rf_renderer_get_physical_screen_height();
    physical_screen_width = rf_renderer_get_physical_screen_width();
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_663058,
      0,
      0,
      physical_screen_width,
      physical_screen_height,
      0,
      0,
      v8,
      v11[0],
      0,
      0,
      (int)v13);
    rf_renderer_present_with_full_viewport();
    v13 = (char *)unk_187CD38;
    v11[0] = level_extent;
    v9 = v39[0];
    v6 = rf_renderer_get_physical_screen_height();
    v1 = rf_renderer_get_physical_screen_width();
    rf_bitmap_blit_subrectangle_backend_dispatch(dword_663058, 0, 0, v1, v6, 0, 0, v9, v11[0], 0, 0, (int)v13);
    rf_renderer_present_with_full_viewport();
    v13 = (char *)unk_187CD38;
    v11[0] = level_extent;
    v10 = v39[0];
    v7 = rf_renderer_get_physical_screen_height();
    v2 = rf_renderer_get_physical_screen_width();
    rf_bitmap_blit_subrectangle_backend_dispatch(dword_663058, 0, 0, v2, v7, 0, 0, v10, v11[0], 0, 0, (int)v13);
  }
  rf_startup_load_hook_noop(0);
  rf_frontend_reset_character_theme_and_clock();
  rf_startup_load_hook_noop(0);
  rf_random_seed_and_discard_two(0xFFFFFFFF);
  rf_startup_load_hook_noop(0);
  rf_startup_load_hook_noop(0);
  if ( rf_command_line_bool_option_is_enabled(byte_88E45C) )
  {
    argument = rf_command_line_option_get_argument(byte_88E45C);
    v23 = Str;
    v22 = Str;
    do
    {
      v21 = *argument;
      *v23 = v21;
      ++argument;
      ++v23;
    }
    while ( v21 );
    rf_path_replace_last_dot_suffix_unbounded(Str, Str, ".rfl");
    Source = Str;
    last_char_wrapper = rf_cstring_find_last_char_wrapper(Str, 92);
    if ( last_char_wrapper )
      Source = last_char_wrapper + 1;
    v26 = &v12;
    v20 = rf_string_construct_from_cstr(&v12, (char *)&byte_63D3DB);
    v19 = v20;
    v42 = 0;
    v25 = v11;
    v18 = rf_string_construct_from_cstr(v11, Source);
    v42 = -1;
    rf_level_transition_assign_level_and_save_strings(v11[0], (char *)v11[1], v12, v13);
  }
  else
  {
    rf_level_reset_auxiliary_name_string();
  }
  rf_game_constants_parse();
  sub_4451D0();
  rf_console_initialize_once_and_load_history(1);
  rf_geomod_cutter_registry_init();
  rf_geomod_history_initialize_ring_and_register_cleanup();
  rf_particle_pools_initialize();
  rf_startup_load_hook_noop(0);
  rf_particle_emitter_system_initialize();
  rf_startup_load_hook_noop(0);
  rf_bolt_emitter_register_empty_exit_hook();
  rf_startup_load_hook_noop(0);
  rf_glare_initialize_list_load_definitions_register_shutdown();
  rf_startup_load_hook_noop(0);
  if ( byte_704E83 != 1 )
  {
    rf_sound_preload_bluebeard_btz_list();
    rf_startup_load_hook_noop(0);
  }
  sub_446820();
  rf_startup_load_hook_noop(0);
  rf_material_system_init();
  rf_startup_load_hook_noop(0);
  rf_scene_effects_enable_named_source_cache();
  rf_vclip_initialize_definition_and_runtime_state();
  rf_startup_load_hook_noop(0);
  rf_object_lists_and_free_slots_initialize_once();
  rf_hud_initialize();
  rf_startup_load_hook_noop(0);
  rf_ammo_initialize_registry_and_register_string_cleanup();
  rf_startup_load_hook_noop(0);
  sub_50D2E0();
  rf_startup_load_hook_noop(0);
  sub_440A40();
  rf_startup_load_hook_noop(0);
  rf_fpgun_load_type_table();
  v38 = rf_performance_clock_elapsed_scaled(1000);
  rf_entity_initialize_definitions_and_shared_effect_resources();
  rf_startup_load_hook_noop(0);
  v39[1] = rf_performance_clock_elapsed_scaled(1000);
  rf_ai_global_initialize_exit_hook();
  rf_waypoint_list_registry_process_initialize();
  rf_item_system_initialize();
  rf_startup_load_hook_noop(0);
  rf_physical_debris_list_init();
  rf_glass_register_empty_exit_hook();
  rf_trigger_registry_initialize();
  rf_ambient_sound_system_construct();
  rf_clutter_registry_initialize_and_warm_textures();
  rf_startup_load_hook_noop(0);
  rf_multiplayer_process_initialize();
  rf_mission_event_registry_initialize();
  rf_corpse_initialize_list_count_register_shutdown();
  rf_startup_load_hook_noop(0);
  rf_volume_system_initialize();
  rf_lightmap_set_generation_preset(0, 1);
  rf_world_decal_pool_initialize();
  rf_procedural_bitmap_pool_initialize();
  rf_mover_registries_initialize();
  rf_startup_load_hook_noop(0);
  rf_monitor_list_initialize_and_register_shutdown();
  rf_level_text_sound_handles_initialize();
  rf_startup_load_hook_noop(0);
  rf_weapon_selector_initialize(v3);
  rf_camera_initialize_two_slots_and_sample_arrays();
  rf_cutscene_register_atexit_cleanup();
  rf_firing_effect_ring_initialize16();
  rf_startup_load_hook_noop(0);
  sub_43E740();
  rf_mesh_decal_pools_reset();
  rf_savegame_initialize_path_and_ponr();
  rf_player_initialize_undercover_profile_strings();
  rf_explosion_definitions_load_table();
  rf_startup_load_hook_noop(0);
  rf_ui_initialize_presentation();
  if ( byte_704E83 != 1 )
  {
    v17 = dword_88E12C;
    rf_ui_label_initialize_measured_text(dword_88E490, 0, 0, 0, dword_88E12C, rf_pause_font);
    unk_88E49C = (640 - unk_88E4A4) / 2;
    unk_88E4A0 = (480 - unk_88E4A8) / 2 - 64;
    rf_ui_button_set_focus(dword_88E490);
    rf_credits_append_localized_table_wrapped_lines();
  }
  rf_startup_load_hook_noop(0);
  if ( byte_704E83 != 1 )
  {
    rf_ui_modal_build_controls();
    rf_input_bindings_initialize_defaults(rf_local_fpgun_player + 228);
  }
  if ( byte_704E83 == 1 )
  {
    rf_multiplayer_start_dedicated_runtime();
    rf_client_level_entry_initialize_and_request_panel5();
  }
  else
  {
    v33 = 0;
    v34 = rf_performance_clock_elapsed_scaled(1000);
    do
    {
      if ( v34 - unk_88E410 >= 3000 )
        break;
      rf_thread_sleep_milliseconds(0x32u);
      v34 = rf_performance_clock_elapsed_scaled(1000);
      ++v33;
    }
    while ( !rf_input_event_queue_not_empty() );
    rf_startup_route_pending_level_or_main_menu();
  }
  rf_console_output_append_text_lines("-- Red Faction Initialized --\n", nullptr);
  unk_88E454 = 0;
  v40 = (char *)&off_663090;
  if ( off_663090 != &unk_1010101 )
  {
    v32 = *(_DWORD *)v40;
    v40 = aReadTheFoundat;
    v30 = 0;
    for ( HIDWORD(Time) = 0; ; ++HIDWORD(Time) )
    {
      v16 = v40;
      v15 = (unsigned __int8 *)(v40 + 1);
      v16 += strlen(v16);
      v14 = ++v16 - (v40 + 1);
      if ( SHIDWORD(Time) >= v14 )
        break;
      v30 += v40[HIDWORD(Time)];
      v29 = (v30 & 1) != 0;
      v30 >>= 1;
      if ( v29 )
        v30 |= 0x80000000;
    }
    v30 |= 0x80000000;
    if ( v30 != v32 )
      unk_88E454 = 1;
    v40 = (char *)&off_663094;
    if ( off_663094 != &unk_2020202 )
    {
      v27 = *(_DWORD *)v40;
      rf_time64_forward_optional_output(&Time);
      if ( (int)Time > v27 )
        unk_88E454 = 2;
    }
    v40 = aReadTheFoundat;
    while ( 1 )
    {
      rf_renderer_clear_color_backend_dispatch();
      rf_render_color_set_rgba8(200, 200, 200, 255);
      rf_font_draw_text_screen(0x8000, 100, "This version of Red Faction has been compiled for", -1, dword_182ABBC);
      rf_font_draw_text_screen(0x8000, 150, (unsigned __int8 *)v40, -1, dword_182ABBC);
      rf_font_draw_text_screen(0x8000, 250, "Press any key to continue.", -1, dword_182ABBC);
      if ( rf_input_dequeue_event() )
        break;
      rf_ui_draw_cursor_and_present();
    }
  }
  rf_startup_load_hook_noop(0);
  rf_text_parser_set_shared_archive_buffer(nullptr, -1, nullptr);
  rf_gameplay_assets_preload();
  rf_console_execute_script_file("gamestart.txt");
  rf_ui_noop_447bd0();
  rf_model_caches_mark_all_retained();
  return atexit(rf_clear_level_strings_and_parser_text_state);
}

