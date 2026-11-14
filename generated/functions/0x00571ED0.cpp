// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571ED0 rf_render_color_set_packed_rgba8
// UNREALRED VERIFIED [hud-status-tint-general] Reads four consecutive bytes from a packed RGBA value and forwards them to rf_render_color_set_rgba8 in R, G, B, A order.
char __cdecl rf_render_color_set_packed_rgba8(unsigned __int8 *a1)
{
  return rf_render_color_set_rgba8(*a1, a1[1], a1[2], a1[3]);
}

