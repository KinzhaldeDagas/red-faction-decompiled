// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00466BC0 rf_host_menu_enter_and_build
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg;panel32 dispatcher supplies no args. If buildBYTE6F5E50 zero,set latch BEFORE constructing titlebar/Create Game label and4 contiguous68-byte
// buttons6F5EE8:Options key24->setup toggle466670,Adv.Options30->rules4666B0,Start31->4666F0,Back48->466930. Append each to inline4 draw/focus lists6F5E80/94,ignore results. Native
// English fallbacks and localized pointer loads verified. EVERY entry invokes setup/catalog builder and rules builder via existing verified names,sets
// buttonX=closedX,paneX=6F29C8,begins opening/sound49,sets pane speed0 then disables/hides467320 (may overwrite speed if old current!=-1),focus0,current/pending=-1,mainInput6F5E28=1.
// Finally toggle setup with two ignored(0,0) words:pending0,NEGATED pane speed,input1 while current remains-1 until animation endpoint. Does not explicitly initialize
// titleX6F5E44,reset LAN byte or runtime/session. No partial-build rollback;build latch remains across entries.
void rf_host_menu_enter_and_build()
{
  if ( !unk_6F5E50 )
  {
    unk_6F5E50 = 1;
    rf_ui_panel_initialize_bitmap(dword_6F5E54, "titlebar.tga", unk_6F29C4, unk_6F29B8);
    rf_ui_label_initialize_measured_text(dword_6F5EA8, (int)dword_6F5E54, 140, 12, unk_88E184, rf_pause_font);
    rf_ui_image_button_initialize(
      dword_6F5EE8,
      "button_more.tga",
      "button_selected.tga",
      rf_main_menu_closed_x,
      rf_main_menu_first_enabled_row_y,
      24,
      unk_88D4E4,
      unk_6F29A8);
    unk_6F5F08 = rf_host_menu_toggle_setup_pane;
    rf_inline_dword_array4_append_unchecked(unk_6F5E80, (int)dword_6F5EE8);
    rf_inline_dword_array4_append_unchecked(unk_6F5E94, (int)dword_6F5EE8);
    rf_ui_image_button_initialize(
      dword_6F5F2C,
      "button_more.tga",
      "button_selected.tga",
      rf_main_menu_closed_x,
      unk_6F5F00 + rf_main_menu_first_enabled_row_y,
      30,
      unk_88E03C,
      unk_6F29A8);
    unk_6F5F4C = rf_host_menu_toggle_rules_pane;
    rf_inline_dword_array4_append_unchecked(unk_6F5E80, (int)dword_6F5F2C);
    rf_inline_dword_array4_append_unchecked(unk_6F5E94, (int)dword_6F5F2C);
    rf_ui_image_button_initialize(
      dword_6F5F70,
      "button.tga",
      "button_selected.tga",
      rf_main_menu_closed_x,
      unk_6F5F00 + unk_6F5F3C,
      31,
      unk_88E040,
      unk_6F29A8);
    unk_6F5F90 = rf_multiplayer_menu_start_host;
    rf_inline_dword_array4_append_unchecked(unk_6F5E80, (int)dword_6F5F70);
    rf_inline_dword_array4_append_unchecked(unk_6F5E94, (int)dword_6F5F70);
    rf_ui_image_button_initialize(
      dword_6F5FB4,
      "button.tga",
      "button_selected.tga",
      rf_main_menu_closed_x,
      unk_6F5F00 + unk_6F5F80,
      48,
      unk_88E048,
      unk_6F29A8);
    unk_6F5FD4 = rf_host_menu_request_back;
    rf_inline_dword_array4_append_unchecked(unk_6F5E80, (int)dword_6F5FB4);
    rf_inline_dword_array4_append_unchecked(unk_6F5E94, (int)dword_6F5FB4);
  }
  rf_multiplayer_setup_build_level_catalog_and_controls();
  rf_multiplayer_rules_build_controls_once();
  unk_6F5E38 = (float)rf_main_menu_closed_x;
  unk_6F5E2C = (float)unk_6F29C8;
  rf_host_menu_begin_open_animation();
  unk_6F5E4C = 0.0;
  rf_host_menu_disable_pane_input_and_hide();
  dword_6F5E34 = 0;
  unk_6F5E30 = -1;
  unk_6F5E3C = -1;
  unk_6F5E28 = 1;
  rf_host_menu_toggle_setup_pane();
}

