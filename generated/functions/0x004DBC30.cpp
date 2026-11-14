// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DBC30 rf_weapon_selector_initialize
// UNREALRED VERIFIED [weapon-selector] Clears the 32-entry selector icon cache and resolves the Hud Weapon Display Scroll, On, Select, and Off foley events.
int __thiscall rf_weapon_selector_initialize(void *this)
{
  int name; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]

  sub_4DBE30();
  dword_87C324 = 0;
  unk_87C528 = -1;
  unk_87C320 = -1;
  dword_87C31C = -1;
  unk_87C52C = 1;
  rf_replicator_reset(&rf_manual_respawn_gate_event);
  rf_local_player_entry_count = 0;
  for ( i = 0; i < 2; ++i )
    rf_local_player_entries[i] = 0;
  if ( byte_704E83 == 1 )
    rf_local_fpgun_player = 0;
  else
    rf_local_fpgun_player = (int)rf_player_create_runtime(1u);
  rf_fpgun_assets_initialize();
  rf_vehicle_cockpit_initialize_camera_sound_and_cleanup();
  flt_87C67C = -0.359;
  unk_87C680 = 0.0;
  unk_87C684 = 0.0;
  flt_87C68C = 0.87266499;
  unk_87C690 = 0.0;
  unk_87C694 = 0.0;
  unk_6FC3B4 = 0;
  for ( j = 0; j < 32; ++j )
    rf_weapon_selector_icon_cache[j] = -1;
  name = rf_foley_definition_find_name("Hud Weapon Display Scroll");
  rf_weapon_selector_scroll_sound_event = rf_foley_get_sound_by_index(name, 0);
  v2 = rf_foley_definition_find_name("Hud Weapon Display On");
  rf_weapon_selector_on_sound_event = rf_foley_get_sound_by_index(v2, 0);
  v3 = rf_foley_definition_find_name("Hud Weapon Display Select");
  rf_weapon_selector_select_sound_event = rf_foley_get_sound_by_index(v3, 0);
  v4 = rf_foley_definition_find_name("Hud Weapon Display Off");
  rf_weapon_selector_off_sound_event = rf_foley_get_sound_by_index(v4, 0);
  return atexit(rf_players_destroy_list_and_shutdown_presentation);
}

