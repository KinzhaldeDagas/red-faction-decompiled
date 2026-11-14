// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E710 rf_renderer_draw_projected_line_backend_wrapper
// UNREALRED VERIFIED [renderer-polygons-20261028]: If backendselector0x187CC9C==102,passes two48-byte vertex pointers and packedstate to rf_renderer_clip_and_draw_projected_line0x5D9620 and returns its byte result. Other backends return0 without drawing. No extra transformation or color handling.
char __cdecl rf_renderer_draw_projected_line_backend_wrapper(int a1, int a2, int a3)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_clip_and_draw_projected_line(a1, a2, a3);
  else
    return 0;
}

