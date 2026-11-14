// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448CB0 rf_pause_overlay_render
// UNREALRED VERIFIED [hud-late-pass] For game modes 11 and 24, lazily creates centered PAUSED text 64 logical pixels above center, draws a half-alpha black physical-display backing, then renders the focused UI root.
int rf_pause_overlay_render()
{
  int result; // eax

  result = rf_ui_panel_stack_current_id();
  if ( result == 11 || result == 24 )
  {
    if ( !rf_pause_overlay_initialized )
    {
      rf_ui_label_initialize_measured_text(rf_pause_overlay_ui_root, 0, 0, 0, "PAUSED", rf_pause_font);
      rf_pause_text_x = (640 - rf_pause_text_width) / 2;
      rf_pause_text_y = (480 - rf_pause_text_height) / 2 - 64;
      rf_ui_button_set_focus(rf_pause_overlay_ui_root);
      rf_pause_overlay_initialized = 1;
    }
    rf_pause_overlay_backing_render(1, 1.0);
    return rf_ui_label_render((int)rf_pause_overlay_ui_root);
  }
  return result;
}

