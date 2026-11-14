// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449620 rf_gameplay_assets_preload
// UNREALRED VERIFIED [combat-selected-drop-resource-20261111]: Gameplay preload loops the actual weapon count. Every nonempty WeaponInfo+0x28 third-person V3D name loads V3M mode1(name,1,-1) and publishes handle+0x30. A missing nonempty resource is fatal in this preload. Thus 50FFA0 availability does not depend on a visible equipped component or item-model alias. First-person resources are loaded separately later from+0x40.
int rf_gameplay_assets_preload()
{
  char *v0; // eax
  char *v1; // eax
  char *v2; // eax
  const char *v3; // eax
  char *v4; // eax
  char *v5; // eax
  char *v6; // eax
  char *v7; // eax
  char *v8; // eax
  char *v9; // eax
  int v11; // [esp+8h] [ebp-12Ch]
  char Buffer[256]; // [esp+Ch] [ebp-128h] BYREF
  const char *v13; // [esp+110h] [ebp-24h]
  const char **v14; // [esp+114h] [ebp-20h]
  int j; // [esp+118h] [ebp-1Ch]
  int v16; // [esp+11Ch] [ebp-18h]
  int v17; // [esp+120h] [ebp-14h]
  char *v18; // [esp+128h] [ebp-Ch]
  int i; // [esp+12Ch] [ebp-8h]
  int index_by_name; // [esp+130h] [ebp-4h]

  v17 = rf_performance_clock_elapsed_scaled(1000);
  for ( i = 0; i < dword_911C68; ++i )
  {
    v14 = (const char **)((char *)&rf_weapon_records + 1360 * i);
    v0 = (char *)rf_string_object_c_str_or_empty(v14 + 302);
    rf_v3m_cache_get_with_default_limit(v0, 1, (void *)0xFFFFFFFF);
    v1 = (char *)rf_string_object_c_str_or_empty(v14 + 307);
    rf_v3m_cache_get_with_default_limit(v1, 1, (void *)0xFFFFFFFF);
    for ( j = 0; j < (int)v14[276]; ++j )
    {
      v13 = v14[j + 277];
      if ( (int)v13 > 0 )
        rf_vclip_preload_scene_definition((int)v13);
    }
    if ( (int)rf_string_length_from_cstr(v14 + 10) > 0 )
    {
      v2 = (char *)rf_string_object_c_str_or_empty(v14 + 10);
      v14[12] = (const char *)rf_model_handle_load_v3m_mode1(v2, 1, (void *)0xFFFFFFFF);
      if ( !v14[12] )
      {
        v3 = rf_string_object_c_str_or_empty(v14 + 10);
        sprintf(Buffer, "Error loading third person weapon mesh: %s", v3);
        rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\gamesrc\\gamewide\\gamewide.cpp", 2332, Buffer);
      }
    }
  }
  index_by_name = rf_clutter_class_find_index_by_name("riot_shield");
  if ( index_by_name >= 0 )
  {
    v11 = dword_667038[58 * index_by_name];
    switch ( v11 )
    {
      case 1:
        v4 = (char *)rf_string_object_c_str_or_empty((char *)&unk_667008 + 232 * index_by_name);
        rf_v3m_cache_get_with_default_limit(v4, 1, (void *)0xFFFFFFFF);
        break;
      case 2:
        v5 = (char *)rf_string_object_c_str_or_empty((char *)&unk_667008 + 232 * index_by_name);
        rf_character_cache_lookup_adapter(v5, 0);
        break;
      case 3:
        v6 = (char *)rf_string_object_c_str_or_empty((char *)&unk_667008 + 232 * index_by_name);
        rf_scene_definition_cache_lookup_adapter(v6, (int)byte_98967F);
        break;
    }
  }
  dword_87C6DC = (int)rf_vfx_load_instance("RailRifleGlow.VFX", (int)byte_98967F);
  dword_87C6E0 = (int)rf_vfx_load_instance("RiotShieldBreak.VFX", (int)byte_98967F);
  rf_scene_definition_cache_lookup_adapter("respawn.vfx", (int)byte_98967F);
  for ( i = 0; i < dword_911C68; ++i )
  {
    v18 = (char *)&rf_weapon_records + 1360 * i;
    if ( (*((_DWORD *)v18 + 153) & 0x80) != 0 || rf_string_is_empty((int *)v18 + 16) )
    {
      *((_DWORD *)v18 + 18) = 0;
    }
    else
    {
      v7 = (char *)rf_string_object_c_str_or_empty(v18 + 64);
      *((_DWORD *)v18 + 18) = rf_model_handle_load_character_instance(v7, 0, 0);
      for ( j = 0; j < 3; ++j )
        rf_weapon_load_named_animation_entry(*((_DWORD *)v18 + 18), i, (char *)rf_fpgun_state_names[j], 1);
      for ( j = 0; j < 12; ++j )
        rf_weapon_load_named_animation_entry(*((_DWORD *)v18 + 18), i, (char *)rf_fpgun_action_names[j], 0);
    }
    if ( (int)rf_string_length_from_cstr((const char **)v18 + 336) > 0 )
    {
      v8 = (char *)rf_string_object_c_str_or_empty(v18 + 1344);
      *((_DWORD *)v18 + 338) = rf_vfx_load_instance(v8, (int)byte_98967F);
      rf_vfx_start_instance(*((int **)v18 + 338), 0, 1.0, 1);
    }
  }
  v16 = rf_item_definition_find_by_name("silenced 12mm handgun");
  if ( v16 == -1 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\gamewide\\gamewide.cpp",
      2399,
      "Could not find item \"silenced 12mm handgun\"");
  v9 = (char *)rf_string_object_c_str_or_empty((char *)&unk_6F9138 + 80 * v16);
  unk_911CE4 = rf_model_handle_load_v3m_mode1(v9, 1, (void *)0xFFFFFFFF);
  rf_performance_clock_elapsed_scaled(1000);
  return atexit(rf_destroy_two_global_models_and_clear_handles);
}

