// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571E50 rf_render_color_set_rgba8
// UNREALRED VERIFIED [hud-status-tint-general] Sets all four current render-color bytes R, G, B, and A when any channel differs, then invalidates the active backend state when required.
char __cdecl rf_render_color_set_rgba8(int a1, int a2, int a3, int a4)
{
  char result; // al

  if ( a1 != rf_render_current_red
    || a2 != rf_render_current_green
    || a3 != rf_render_current_blue
    || (result = rf_render_current_alpha, a4 != rf_render_current_alpha) )
  {
    rf_render_current_red = a1;
    rf_render_current_green = a2;
    result = a3;
    rf_render_current_blue = a3;
    rf_render_current_alpha = a4;
    if ( dword_187CC9C == 102 )
      return rf_renderer_flush_immediate_wrapper();
  }
  return result;
}

