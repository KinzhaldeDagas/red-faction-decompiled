// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448C20 rf_pause_overlay_backing_render
// UNREALRED VERIFIED [hud-late-pass] Draws a black overlay with alpha min(trunc(scale*128),255), selecting physical-display dimensions when requested and viewport dimensions otherwise.
int __cdecl rf_pause_overlay_backing_render(char a1, float a2)
{
  int physical_screen_width; // eax
  int physical_screen_height; // [esp-8h] [ebp-Ch]
  int v5; // [esp-4h] [ebp-8h]
  int v6; // [esp+0h] [ebp-4h]

  v6 = (int)(a2 * 128.0);
  if ( v6 > 255 )
    v6 = 255;
  rf_render_color_set_rgba8(0, 0, 0, v6);
  v5 = dword_182ABB8;
  if ( a1 )
  {
    physical_screen_height = rf_renderer_get_physical_screen_height();
    physical_screen_width = rf_renderer_get_physical_screen_width();
  }
  else
  {
    physical_screen_height = rf_renderer_get_viewport_height();
    physical_screen_width = rf_renderer_get_viewport_width();
  }
  return rf_renderer_fill_rectangle_clipped(0, 0, physical_screen_width, physical_screen_height, v5);
}

