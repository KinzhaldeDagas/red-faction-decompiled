// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571F00 rf_render_color_set_alpha8
// UNREALRED VERIFIED [hud-status-tint-general] Reuses the current render R, G, and B bytes while replacing only alpha through rf_render_color_set_rgba8.
char __cdecl rf_render_color_set_alpha8(int a1)
{
  return rf_render_color_set_rgba8(rf_render_current_red, rf_render_current_green, rf_render_current_blue, a1);
}

