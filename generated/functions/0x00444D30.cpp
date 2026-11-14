// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00444D30 sub_444D30
// UNREALRED VERIFIED [combat-native-ai-dependencies-20261111] Shared6FC428 advances by one binary32 store of old float+frame-delta seconds BEFORE object physics and event/world managers, after native pause/client gates. It is independent of deadline millisecond ring. Unreal pre-actor delegate uses clamped/dilated UE delta and is an explicit host phase adapter; do not derive this float sequence from a double millisecond clock or claim native MP client-sync parity.
// [UnrealRed combat room owner 2026-11-12; verified original-byte ASM] Physics/object update4B8FB0 includes late global cached-room refresh early in this simulation update. Active burn updater43F270 occurs LATER at444F22 after other effects/events. Thus ordinary AI/attached emitters beforelateRoomRefresh consume prior cache, while active burn emission afterlateRoomRefresh consumes refreshed cache. Do not reverse burn and room phases based on AI ordering alone.
// UNREALRED VERIFIED [combat-burn-pool-phases-20261112]: Original 444D30 has TWO independently admitted authored/RFL emitter scheduling passes: 444EB9 before managed effects, firing ring, explosion graphs and Burn43F270; 444FB0 after particle advance4CCBB0 and the later4CEEF0 call. Both are inside the broad pause/client gate (pause AL!=1 AND (MPbyte!=1 OR serverAuthority!=0 OR mode446190()==34 OR localFpgun+1200->flags+8 bit20 clear)). Each pass starts a fresh ordered registry iteration, re-reads current count/entries, and calls4CDF40 only when4CE040 returns nonzero raw cached-room BYTE352. 4CDF40 separately gates globalbyte662DF4 and its own state/deadlines. Do not interpret this as unconditional double emission or collapse it to one generic all-pool emitter tick. 4CCBB0 advances unowned particles, embedded lists of all active emitters and the detached list; it is not emitter scheduling. Exact ASM branch predicates and all18 aligned direct4CEC90 sites across10 consumer families are recorded in combat_burn_init
void sub_444D30()
{
  int *v0; // eax
  _DWORD **v1; // eax
  int *v2; // eax
  float v3; // [esp+0h] [ebp-10h]
  _DWORD *v4; // [esp+4h] [ebp-Ch]
  _DWORD *v5; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]
  int j; // [esp+Ch] [ebp-4h]
  int k; // [esp+Ch] [ebp-4h]
  int m; // [esp+Ch] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 )
    rf_motion_sample_buffers_advance_registered_objects();
  if ( rf_game_pause_gate_query() != 1
    && (rf_multiplayer_runtime_mode != 1
     || rf_multiplayer_server_authority
     || rf_ui_panel_stack_current_id() == 34
     || (*(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) & 0x20) == 0) )
  {
    *(float *)&dword_6FC428 = *(float *)&dword_6FC428 + rf_frame_delta_seconds;
    unk_6FC42C = unk_6FC42C + rf_frame_delta_seconds;
    if ( rf_mission_countdown_remaining_seconds > 0.0 )
    {
      rf_mission_countdown_remaining_seconds = rf_mission_countdown_remaining_seconds - rf_frame_delta_seconds;
      if ( rf_mission_countdown_remaining_seconds < 0.0 )
      {
        unk_6FC424 |= 2u;
        rf_mission_countdown_remaining_seconds = 0.0;
      }
    }
    dword_681E70 = 0;
    rf_object_physics_frame_update();
    for ( i = 0; i < rf_receiver_get_first_dword(rf_rfl_light_registry); ++i )
    {
      v3 = rf_frame_delta_seconds;
      v0 = (int *)sub_552200(rf_rfl_light_registry, i);
      rf_rfl_light_update_changing(*v0, v3);
    }
    rf_world_step_uv_scroll_and_authored_sky_liquid(rf_world_solid, rf_frame_delta_seconds);
    for ( j = 0; j < rf_receiver_get_first_dword(rf_particle_emitter_registry); ++j )
    {
      v1 = (_DWORD **)sub_552200(rf_particle_emitter_registry, j);
      if ( rf_particle_emitter_cached_room_visibility_byte(*v1) )
      {
        v2 = (int *)sub_552200(rf_particle_emitter_registry, j);
        rf_particle_emitter_process(*v2);
      }
    }
    rf_managed_particle_effect_list_process(flt_6FC400);
    rf_projectile_update_parent_attachments();
    if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
      rf_object_respawn_update_authority();
    rf_camera_update_occupied_slots();
    rf_item_limit_dropped_population_update();
    rf_mission_event_registry_update();
    rf_vclip_effect_update_all();
    rf_liquid_room_level_update();
    rf_trigger_global_lifecycle_update();
    rf_monitor_update_registry();
    rf_firing_effect_ring_process_selected_pair();
    rf_blood_surface_marks_advance_age();
    rf_rail_trail_update_and_recycle();
    rf_explosion_graph_update_runtime();
    sub_43F270();
    rf_particle_emitter_extent_prepare_disabled_noop();
    rf_particle_update_all_live_lists(rf_frame_delta_seconds);
    if ( byte_704E83 != 1 )
    {
      rf_glass_shard_system_update();
      rf_geomod_impact_chunks_update_motion_damage_audio();
    }
    if ( byte_704E83 != 1 )
      rf_local_players_update_runtime();
    rf_particle_emitter_extent_finish_frame();
    for ( k = 0; k < rf_receiver_get_first_dword(rf_particle_emitter_registry); ++k )
    {
      v5 = *(_DWORD **)sub_552200(rf_particle_emitter_registry, k);
      if ( rf_particle_emitter_cached_room_visibility_byte(v5) )
        rf_particle_emitter_process((int)v5);
    }
    for ( m = 0; m < rf_receiver_get_first_dword(rf_bolt_emitter_registry); ++m )
    {
      v4 = *(_DWORD **)sub_552200(rf_bolt_emitter_registry, m);
      if ( rf_bolt_emitter_get_room_byte352(v4) )
        rf_bolt_emitter_tick_slots((int)v4);
    }
    if ( rf_skybox_rotation_degrees_per_second > 0.0 )
    {
      rf_skybox_rotation_angle_degrees = rf_skybox_rotation_degrees_per_second * rf_frame_delta_seconds
                                       + rf_skybox_rotation_angle_degrees;
      rf_skybox_build_axis_rotation(rf_skybox_rotation_matrix);
    }
    if ( rf_multiplayer_runtime_mode == 1 )
      rf_motion_sample_buffers_clear_registered_snap_flags();
  }
}

