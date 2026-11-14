// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00477770 rf_level_destroy_runtime_resources
// UNREALRED VERIFIED [level-lifecycle-20261028]: Drains rf_geomod_operation_step until false, destroys ambient records/stops voice slots/releases unreferenced sound with multiplayer flag, runs0x54ADA0/0x5264C0 and clears geometry context through0x526300(0,0). Destroys world solid if nonnull then clears pointer. Destroys particle emitter records and clears slots, bolt and RFL light records through scalar-delete wrappers, raw-deletes georegion/OBB-region/push-region records, releases each registry backing array. Calls0x4C1730(global0x6FC400), clears level flags0x6FC424, disables event removed-UID tracking around object cleanup0x4BCB20 then reenables it. Runs0x4C5ED0/0x4E4C40, clears event registry, parser scratch0x4838A0, all monitors0x417640, effect pools0x4C2050/0x506840, cutscene registries0x475EE0, then0x48B360/0x4397B0/0x4CB140/0x4BDAF0/0x5213D0/0x53A0A0. Unless global0x704E83==1,
// clears resolved local entity+5076 to-1 and resets player view via0x4123C0. Returns0x578720 result. Object cleanup intentionally preserves selected flag-marked objects outside panel13; not all runtime objects are unconditionally freed. No cutscene end/restore call in this body; callers must manage active playback.
int rf_level_destroy_runtime_resources()
{
  int *v0; // eax
  void **v1; // eax
  void **v2; // eax
  void **v3; // eax
  void *v5; // [esp+1Ch] [ebp-1Ch]
  void *v6; // [esp+24h] [ebp-14h]
  int v7; // [esp+30h] [ebp-8h]
  int i; // [esp+34h] [ebp-4h]
  int j; // [esp+34h] [ebp-4h]
  int k; // [esp+34h] [ebp-4h]
  int m; // [esp+34h] [ebp-4h]
  int n; // [esp+34h] [ebp-4h]
  int ii; // [esp+34h] [ebp-4h]

  while ( rf_geomod_operation_step() )
    ;
  rf_ambient_sound_destroy_all_wrapper();
  rf_gamesound_stop_all_voice_slots();
  rf_sound_release_unreferenced(rf_multiplayer_runtime_mode);
  rf_scratch_arena_rewind_and_clear_owners();
  rf_geometry_free_context_circular_blocks();
  rf_geometry_set_current_context(0, 0);
  if ( rf_world_solid )
    rf_solid_destroy((char *)rf_world_solid, 1);
  rf_world_solid = 0;
  for ( i = 0; i < rf_receiver_get_first_dword(rf_particle_emitter_registry); ++i )
  {
    if ( *(_DWORD *)sub_552200(rf_particle_emitter_registry, i) )
    {
      v0 = (int *)sub_552200(rf_particle_emitter_registry, i);
      rf_particle_emitter_destroy(*v0);
      *(_DWORD *)sub_552200(rf_particle_emitter_registry, i) = 0;
    }
  }
  rf_pointer_array_release_storage((void **)rf_particle_emitter_registry);
  for ( j = 0; j < rf_receiver_get_first_dword(rf_bolt_emitter_registry); ++j )
  {
    if ( *(_DWORD *)sub_552200(rf_bolt_emitter_registry, j) )
    {
      v6 = *(void **)sub_552200(rf_bolt_emitter_registry, j);
      if ( v6 )
        rf_bolt_emitter_scalar_delete(v6, 1);
    }
  }
  rf_pointer_array_release_storage((void **)rf_bolt_emitter_registry);
  for ( k = 0; k < rf_receiver_get_first_dword(rf_rfl_light_registry); ++k )
  {
    if ( *(_DWORD *)sub_552200(rf_rfl_light_registry, k) )
    {
      v5 = *(void **)sub_552200(rf_rfl_light_registry, k);
      if ( v5 )
        rf_rfl_light_scalar_delete(v5, 1);
    }
  }
  rf_pointer_array_release_storage((void **)rf_rfl_light_registry);
  for ( m = 0; m < rf_receiver_get_first_dword(rf_geomod_georegion_registry); ++m )
  {
    if ( *(_DWORD *)sub_552200(rf_geomod_georegion_registry, m) )
    {
      v1 = (void **)sub_552200(rf_geomod_georegion_registry, m);
      operator delete(*v1);
    }
  }
  rf_pointer_array_release_storage((void **)rf_geomod_georegion_registry);
  for ( n = 0; n < rf_receiver_get_first_dword(unk_6FC3E8); ++n )
  {
    if ( *(_DWORD *)sub_552200(unk_6FC3E8, n) )
    {
      v2 = (void **)sub_552200(unk_6FC3E8, n);
      operator delete(*v2);
    }
  }
  rf_pointer_array_release_storage((void **)unk_6FC3E8);
  for ( ii = 0; ii < rf_receiver_get_first_dword(rf_push_region_registry); ++ii )
  {
    if ( *(_DWORD *)sub_552200(rf_push_region_registry, ii) )
    {
      v3 = (void **)sub_552200(rf_push_region_registry, ii);
      operator delete(*v3);
    }
  }
  rf_pointer_array_release_storage((void **)rf_push_region_registry);
  rf_managed_particle_effect_list_clear_nodes(flt_6FC400);
  unk_6FC424 = 0;
  rf_mission_event_removed_uid_tracking_disable();
  rf_object_level_cleanup_preserve_marked();
  rf_mission_event_removed_uid_tracking_enable();
  sub_4C5ED0();
  rf_fighter_chaingun_model_release();
  rf_mission_event_registry_atexit_cleanup();
  rf_rfl_clear_parser_scratch();
  rf_monitor_destroy_all_records();
  rf_explosion_graph_pool_destroy_and_reset();
  rf_vclip_effect_pool_clear_for_level();
  rf_cutscene_registries_destroy_all();
  sub_48B360();
  rf_entity_destroy_shared_jeep_model();
  rf_particle_pool_recycle_all_active();
  rf_world_free_model_instance_render_data();
  rf_world_decal_pool_clear_level();
  rf_procedural_bitmap_system_clear();
  if ( byte_704E83 != 1 )
  {
    if ( rf_local_fpgun_player )
    {
      v7 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_fpgun_player + 20));
      if ( v7 )
        *(_DWORD *)(v7 + 5076) = -1;
    }
  }
  if ( byte_704E83 != 1 && rf_local_fpgun_player )
    rf_camera_slot_clear_room(*(float ***)(rf_local_fpgun_player + 196));
  return rf_bitmap_end_residency_scope_unless_suppressed();
}

