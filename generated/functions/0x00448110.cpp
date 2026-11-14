// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448110 rf_hud_late_font_initialize
// UNREALRED VERIFIED [hud-late-pass] Loads rfpc-large.vf for the mission countdown and also initializes rfpc-medium.vf when the alternate presentation backend is not active.
char rf_hud_late_font_initialize()
{
  char result; // al

  result = byte_704E83;
  if ( byte_704E83 != 1 )
  {
    rf_hud_countdown_font = rf_font_load_with_spacing_override("rfpc-large.vf", -1);
    return rf_font_set_default_by_name("rfpc-medium.vf");
  }
  return result;
}

