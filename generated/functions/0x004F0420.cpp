// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F0420 rf_application_initialize_platform_renderer_network
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Registers model-system cache release with atexit; initializes performance clock,CD root,VFile roots(NULL,1),retail loose roots,user-map/mod VPP mounts. Reads Geometry Cache Size DWORD default8, UNSIGNED clamps2..32, allocates value*2^20 bytes. Writes registry Version Major1,Minor21,Build0; initializes bitmap storage,archive metadata and keyboard(0,1,0). Only dedicated BYTE704E83 EXACT1 skips audio/video/mouse block. Otherwise4F0B90 applies sound registry settings; if BYTE88E444==0 initializes sound(mainHWND,22050Hz,16bits,2channels,zero-extended bytes88E3F2/88E445/88E3F0/88E3F1). If screen selector88E44C==-1 calls4F0B00; selector0 sets88E3FC=201. Renderer receives
// width88E40C,height88E418,depth88E424,table66305C[screen selector],88E3FC,HWND,F321000,byte88E446,card88E458,backbuffer663054; no selector/card/range check. Initializes mouse(width,height). Calls optional log setup4A6220 (its4A6760 probe is constant false in this binary). Unless command-line port option88E568 is enabled, reads ForcePort default7755 and updates WORD662868 only for unsigned1..65535. Calls Winsock/UDP initializer with zero-extended port, returns its EAX. No own failure/atexit-registration-result checks or transactional rollback.
int rf_application_initialize_platform_renderer_network()
{
  HWND main_hwnd; // eax
  HWND v1; // eax
  char v3; // [esp+0h] [ebp-30h]
  char v4; // [esp+4h] [ebp-2Ch]
  char v5; // [esp+4h] [ebp-2Ch]
  char v6; // [esp+8h] [ebp-28h]
  int v7; // [esp+8h] [ebp-28h]
  char v8; // [esp+Ch] [ebp-24h]
  int v9; // [esp+Ch] [ebp-24h]
  BYTE v10[4]; // [esp+10h] [ebp-20h] BYREF
  int v11; // [esp+14h] [ebp-1Ch]
  int v12; // [esp+18h] [ebp-18h]
  int v13; // [esp+1Ch] [ebp-14h]
  int v14; // [esp+20h] [ebp-10h]
  int v15; // [esp+24h] [ebp-Ch]
  int v16; // [esp+28h] [ebp-8h]
  BYTE Data[4]; // [esp+2Ch] [ebp-4h] BYREF

  atexit(rf_model_system_release_character_and_asset_caches);
  rf_performance_clock_initialize();
  rf_cd_detect_and_set_root();
  rf_vfile_initialize_roots_and_optional_vpp_mounts(nullptr, 1);
  rf_register_retail_loose_search_roots();
  rf_mount_user_maps_and_active_mod_vpps();
  *(_DWORD *)Data = 8;
  rf_registry_read_dword_or_default(nullptr, "Geometry Cache Size", Data, 8);
  rf_uint32_clamp_in_place((unsigned int *)Data, 2u, 0x20u);
  rf_scratch_arena_allocate(*(_DWORD *)Data << 20);
  rf_registry_write_dword("Version", "Major", 1);
  rf_registry_write_dword("Version", "Minor", 21);
  rf_registry_write_dword("Version", "Build", 0);
  rf_bitmap_manager_initialize_storage();
  rf_archive_collect_startup_metadata();
  rf_input_initialize_keyboard_state(0, 1, 0);
  if ( byte_704E83 != 1 )
  {
    rf_sound_settings_apply_registry_overrides();
    if ( !unk_88E444 )
    {
      v8 = unk_88E3F1;
      v6 = unk_88E3F0;
      v4 = unk_88E445;
      v3 = unk_88E3F2;
      main_hwnd = rf_window_get_main_hwnd();
      rf_gamesound_initialize_level_state((int)main_hwnd, 22050, 16, 2, v3, v4, v6, v8);
    }
    if ( unk_88E44C == -1 )
      rf_video_settings_read_registry_defaults();
    if ( !unk_88E44C )
      unk_88E3FC = 201;
    v16 = *(_DWORD *)byte_88E40C;
    v15 = *(_DWORD *)byte_88E418;
    v14 = *(_DWORD *)MEMORY[0x88E424];
    v13 = dword_66305C[unk_88E44C];
    v12 = *(_DWORD *)byte_88E458;
    v11 = *(_DWORD *)&dword_663054;
    v9 = *(_DWORD *)&dword_663054;
    v7 = *(_DWORD *)byte_88E458;
    v5 = unk_88E446;
    v1 = rf_window_get_main_hwnd();
    rf_renderer_initialize_context_and_window(v16, v15, v14, v13, unk_88E3FC, v1, 1000.0, v5, v7, v9);
    rf_mouse_initialize(v16, v15);
  }
  rf_multiplayer_log_open_if_enabled_stub();
  if ( !rf_command_line_bool_option_is_enabled(byte_88E568) )
  {
    rf_registry_read_dword_or_default(nullptr, "ForcePort", v10, 7755);
    if ( *(_DWORD *)v10 )
    {
      if ( *(_DWORD *)v10 <= 0xFFFFu )
        word_662868 = *(_WORD *)v10;
    }
  }
  return rf_network_initialize_winsock_and_udp(word_662868);
}

