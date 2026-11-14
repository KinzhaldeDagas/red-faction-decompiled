// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057FCC0 rf_renderer_draw_rgb_world_line_components
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Cdecl six floats(startXYZ,endXYZ),three RGB integers,and stateDWORD. Builds two local vectors,sets global color through RGBA8 setter with suppliedRGB/alpha255,then dispatches world line and returns its byte. DOES NOT restore previous global color,including unsupported renderer backend;not a color-preserving debug wrapper.
char __cdecl rf_renderer_draw_rgb_world_line_components(
        float a1,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6,
        int a7,
        int a8,
        int a9,
        int a10)
{
  float v11[3]; // [esp+Ch] [ebp-18h] BYREF
  float v12[3]; // [esp+18h] [ebp-Ch] BYREF

  rf_vector3_set_components_return_destination(v12, a1, a2, a3);
  rf_vector3_set_components_return_destination(v11, a4, a5, a6);
  rf_render_color_set_rgba8(a7, a8, a9, 255);
  return rf_debug_draw_world_line_backend_dispatch(v12, v11, a10);
}

