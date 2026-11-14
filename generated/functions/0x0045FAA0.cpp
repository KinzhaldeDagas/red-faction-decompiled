// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045FAA0 rf_multiplayer_menu_enter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. If buildBYTE6F4869 zero,construct four contiguous68-byte buttons at6F4898:Player(key25)->45F9A0,Join Game36->45F9F0,Create
// Game46->45FA30,Back48->45FA70. Runtime captions localized;original English fallbacks and texture bindings verified. Append pointers to inline20 hit-list6F49A8 and inline4
// focus-list6F49FC;build titlebar6F486C and Multiplayer label6F4A10;set build latch only AFTER construction. EVERY invocation:Join/Create stateBYTE9=!anyNonzero
// activeSession;buttonX6F4854=closedX,button speed6F4858=firstButtonWidth*open_x_speed_scale;titleX6F485C=6F29C4,title speed6F4860=661E60;current/pending
// pane=-1,focus6F484C=0,profileX6F4848=6F29C8,profile speed0. Sound49,initialize profile panel4606C0,then menu inputBYTE6F4868=1. Does not reset profile-inputBYTE6F4850 explicitly or
// start network traffic. These position channels become X coordinates in draw routines;shared constants named vertical elsewhere are reused here. No rollback on construction
// failure;return profile-init residue.
int rf_multiplayer_menu_enter()
{
  int result; // eax

  if ( !unk_6F4869 )
  {
    rf_ui_image_button_initialize(
      (int *)&unk_6F4898,
      "button_more.tga",
      "button_selected.tga",
      0,
      0,
      25,
      unk_88E170,
      unk_6F29A8);
    unk_6F48B8 = rf_multiplayer_menu_toggle_profile_pane;
    rf_inline_dword_array20_append(dword_6F49A8, (int)&unk_6F4898);
    rf_inline_dword_array4_append_unchecked(unk_6F49FC, (int)&unk_6F4898);
    rf_ui_image_button_initialize(
      (int *)&unk_6F48DC,
      "button.tga",
      "button_selected.tga",
      0,
      0,
      36,
      unk_88DF98,
      unk_6F29A8);
    unk_6F48FC = rf_multiplayer_menu_request_join_panel30;
    rf_inline_dword_array20_append(dword_6F49A8, (int)&unk_6F48DC);
    rf_inline_dword_array4_append_unchecked(unk_6F49FC, (int)&unk_6F48DC);
    rf_ui_image_button_initialize(
      (int *)&unk_6F4920,
      "button.tga",
      "button_selected.tga",
      0,
      0,
      46,
      unk_88DF9C,
      unk_6F29A8);
    unk_6F4940 = rf_multiplayer_menu_request_create_panel32;
    rf_inline_dword_array20_append(dword_6F49A8, (int)&unk_6F4920);
    rf_inline_dword_array4_append_unchecked(unk_6F49FC, (int)&unk_6F4920);
    rf_ui_image_button_initialize(dword_6F4964, "button.tga", "button_selected.tga", 0, 0, 48, unk_88E048, unk_6F29A8);
    unk_6F4984 = rf_multiplayer_menu_request_back;
    rf_inline_dword_array20_append(dword_6F49A8, (int)dword_6F4964);
    rf_inline_dword_array4_append_unchecked(unk_6F49FC, (int)dword_6F4964);
    rf_ui_panel_initialize_bitmap(dword_6F486C, "titlebar.tga", unk_6F29C4, unk_6F29B8);
    rf_ui_label_initialize_measured_text(dword_6F4A10, (int)dword_6F486C, 140, 12, unk_88E16C, rf_pause_font);
    unk_6F4869 = 1;
  }
  unk_6F48E5 = rf_main_menu_has_previous_panel == 0;
  unk_6F4929 = rf_main_menu_has_previous_panel == 0;
  unk_6F4854 = (float)rf_main_menu_closed_x;
  unk_6F4858 = (double)unk_6F48AC * rf_main_menu_open_x_speed_scale;
  unk_6F485C = (float)unk_6F29C4;
  unk_6F4860 = flt_661E60;
  dword_661F8C = -1;
  dword_661F90 = -1;
  unk_6F484C = 0;
  unk_6F4848 = (float)unk_6F29C8;
  unk_6F4864 = 0.0;
  rf_gamesound_play_event(49, 0, 0.0, 1.0);
  result = rf_multiplayer_profile_build_and_load();
  unk_6F4868 = 1;
  return result;
}

