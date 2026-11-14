// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459120 rf_main_menu_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments consumed. Clears BYTE182A379. If restart-music DWORD nonzero, calls598740, obtains c_str of RFString6F2C78, calls4590D0 and clears restart
// DWORD0 regardless of returned AL. Sets661E88=1. Only while widgets-initialized BYTE is0: initializes eight68-byte records at6F2A58 in CALL ORDER physical slots0,2,1,3,4,5,6,7, with
// control IDs49,38,31,50,24,19,18,16 and localized pointers88E09C,88E0A0,88E124,88D4F4,88D4E4,88E128,88D4E8,88D4F0. All use button.tga/button_selected.tga, coordinates0,0 and font
// DWORD6F29A8. Constant-zero branches bypass embedded English alternatives. Computes closedX=openX-DWORD6F2A6C with32-bit wrap; creates title6F2C80 using main_title.tga for both
// textures, stored titleY, control0 and source635D29; creates version text widget6F2A18 attached to title with(330,340,120,15), source from4F2EB0 and font6F29AC. Fills pointer
// array6F29E4[i]=6F2A58+68*i for8 entries; warms textures6F2A80,6F2A84,6F2CA8; sets initialized1 even without own failure checks. Every invocation next stores6F29DC=(446170 PREVIOUS
// PANEL ID!=0), not a resolved game-session predicate. Previous-nonzero: enabled slots3=raw multiplayer byte,2/1=(that byte==0),5=1,0=0,6=0. Previous-zero: slots3/2/0/6=1,1/5=0
// and48FEE0 clears startup byte; slots4/7 not explicitly rewritten by this branch. Scans slots0..7, setting selected to first nonzero enabled byte, preserving previous selection if
// none. FILD/FSTP closedX to currentX and DWORD6F29C8 to titleX; calls459520 open,58B6C0 keyboard reset, then interaction-active1. No normalized EAX result, allocation rollback,
// bounds validation or shared-state snapshot across delegates. Physical record order is not the load/save helper-name order in dispatcher; use exact addresses/IDs rather than
// inferring panel identity.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Axis correction verified against native coordinate helpers46FC70/46FCA0 and title initialization: animated title field6F2C8C is receiver6F2C80+12, X.
// Current6F29D8 and velocity6F2A08 are title X; title Y at+16 remains a separate constructor coordinate. Shared661E50 is an opening transition speed, not a universal vertical speed.
// Prior detailed contract retained with corrected axes.
void rf_main_menu_initialize()
{
  const char *v0; // eax
  int j; // [esp+20h] [ebp-10h]
  int i; // [esp+24h] [ebp-Ch]
  char *Source; // [esp+28h] [ebp-8h] BYREF
  int v4; // [esp+2Ch] [ebp-4h]

  unk_182A379 = 0;
  if ( rf_main_menu_restart_music_pending )
  {
    rf_audio_environment_save_room_level_and_mute();
    v0 = rf_string_object_c_str_or_empty(unk_6F2C78);
    rf_main_menu_start_music((int)v0);
    rf_main_menu_restart_music_pending = 0;
  }
  byte_661E88 = 1;
  if ( !rf_main_menu_widgets_initialized )
  {
    rf_ui_image_button_initialize(
      (int *)&rf_main_menu_buttons,
      "button.tga",
      "button_selected.tga",
      0,
      0,
      49,
      unk_88E09C,
      unk_6F29A8);
    rf_ui_image_button_initialize(
      (int *)&unk_6F2AE0,
      "button.tga",
      "button_selected.tga",
      0,
      0,
      38,
      unk_88E0A0,
      unk_6F29A8);
    rf_ui_image_button_initialize(
      (int *)&unk_6F2A9C,
      "button.tga",
      "button_selected.tga",
      0,
      0,
      31,
      unk_88E124,
      unk_6F29A8);
    rf_ui_image_button_initialize(
      (int *)&unk_6F2B24,
      "button.tga",
      "button_selected.tga",
      0,
      0,
      50,
      unk_88D4F4,
      unk_6F29A8);
    rf_ui_image_button_initialize(dword_6F2B68, "button.tga", "button_selected.tga", 0, 0, 24, unk_88D4E4, unk_6F29A8);
    rf_ui_image_button_initialize(
      (int *)&unk_6F2BAC,
      "button.tga",
      "button_selected.tga",
      0,
      0,
      19,
      unk_88E128,
      unk_6F29A8);
    rf_ui_image_button_initialize(
      (int *)&unk_6F2BF0,
      "button.tga",
      "button_selected.tga",
      0,
      0,
      18,
      unk_88D4E8,
      unk_6F29A8);
    rf_ui_image_button_initialize(dword_6F2C34, "button.tga", "button_selected.tga", 0, 0, 16, unk_88D4F0, unk_6F29A8);
    rf_main_menu_closed_x = rf_main_menu_open_x - unk_6F2A6C;
    rf_ui_image_button_initialize(
      dword_6F2C80,
      "main_title.tga",
      "main_title.tga",
      0,
      rf_main_menu_title_y,
      0,
      (char *)&byte_635D29,
      unk_6F29A8);
    rf_build_version_get_string_pointers(&Source, nullptr);
    rf_ui_text_widget_initialize(dword_6F2A18, (int)dword_6F2C80, 330, 340, 120, 15, Source, unk_6F29AC);
    for ( i = 0; i < 8; ++i )
      rf_main_menu_button_pointers[i] = (int)&rf_main_menu_buttons + 68 * i;
    rf_renderer_bind_texture_for_level_warmup(unk_6F2A80);
    rf_renderer_bind_texture_for_level_warmup(unk_6F2A84);
    rf_renderer_bind_texture_for_level_warmup(unk_6F2CA8);
    rf_main_menu_widgets_initialized = 1;
  }
  v4 = rf_ui_panel_stack_previous_id();
  rf_main_menu_has_previous_panel = v4 != 0;
  if ( v4 )
  {
    unk_6F2B2D = rf_multiplayer_runtime_mode;
    unk_6F2AE9 = rf_multiplayer_runtime_mode == 0;
    unk_6F2AA5 = rf_multiplayer_runtime_mode == 0;
    unk_6F2BB5 = 1;
    unk_6F2A61[0] = 0;
    unk_6F2BF9 = 0;
  }
  else
  {
    unk_6F2B2D = 1;
    unk_6F2AE9 = 1;
    unk_6F2AA5 = 0;
    unk_6F2BB5 = 0;
    unk_6F2A61[0] = 1;
    unk_6F2BF9 = 1;
    rf_clear_startup_session_flag();
  }
  for ( j = 0; j < 8; ++j )
  {
    if ( unk_6F2A61[68 * j] )
    {
      rf_main_menu_selected_index = j;
      break;
    }
  }
  rf_main_menu_current_x = (float)rf_main_menu_closed_x;
  rf_main_menu_title_current_x = (float)unk_6F29C8;
  rf_main_menu_begin_open_transition();
  rf_input_reset_all_key_and_event_state();
  rf_main_menu_interaction_active = 1;
}

