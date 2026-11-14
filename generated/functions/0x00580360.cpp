// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580360 rf_font_draw_text_at_world_point
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Transforms world point into temporary clip vertex. Only if transform returns0 calls projection helper;draws text only when temporary projected flags byte+25 has bit0(0x01). Coordinates are truncated projected floats plus supplied integer offsets;passes length-1 and current text state182ABBC to font renderer. No independent frustum/screen rectangle clipping or text copy;char return follows helper/draw result,not a uniform visibility boolean.
char __cdecl rf_font_draw_text_at_world_point(float *a1, unsigned __int8 *a2, int a3, int a4)
{
  char result; // al
  _BYTE v5[12]; // [esp+4h] [ebp-30h] BYREF
  float v6; // [esp+10h] [ebp-24h]
  float v7; // [esp+14h] [ebp-20h]
  char v8; // [esp+1Dh] [ebp-17h]

  rf_vector_prefix_construct_noop(v5);
  result = rf_renderer_transform_world_point_backend_wrapper((int)v5, a1);
  if ( !result )
  {
    result = rf_renderer_project_clip_vertex_backend_wrapper((int)v5);
    if ( (v8 & 1) != 0 )
      return rf_font_draw_text_screen(a3 + (int)v6, a4 + (int)v7, a2, -1, dword_182ABBC);
  }
  return result;
}

