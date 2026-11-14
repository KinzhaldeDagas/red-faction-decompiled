// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A8D0 rf_hud_initialize
// UNREALRED VERIFIED [hud-status-font-20261027] Exact numeric font owners: bootstrap stores bigfont.vf loader result at 0x661690 and smallfont.vf result at 0x661694; font-hud_test.vf uses separate 0x66168C. Do not infer numeric font from the word HUD: on-foot status and vehicle numbers consume the small handle, while ammo counts consume the big handle.
int rf_hud_initialize()
{
  int result; // eax

  result = (unsigned __int8)byte_704E83;
  if ( byte_704E83 != 1 )
  {
    dword_6EE090 = rf_renderer_get_physical_screen_width();
    unk_6EE094 = rf_renderer_get_physical_screen_height();
    rf_hud_table_load_and_select_profile(dword_6EE090);
    dword_66168C = rf_font_load_with_spacing_override("font-hud_test.vf", -1);
    dword_661690 = rf_font_load_with_spacing_override("bigfont.vf", -1);
    dword_661694 = rf_font_load_with_spacing_override("smallfont.vf", -1);
    rf_hud_message_register_noop_atexit_callback();
    rf_hud_personas_load_table();
    rf_hud_message_register_atexit_noop();
    rf_hud_initialize_ammo_bar_bitmaps();
    rf_hud_status_bitmaps_initialize();
    return atexit(rf_hud_noop_callback_44A970);
  }
  return result;
}

