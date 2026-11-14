// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580560 rf_renderer_face_green_overlay_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Backend102 forwards face DWORD to verified green translucent face overlay renderer;otherwise returns low byte of backend value. No local color change or visibility logic.
char __cdecl rf_renderer_face_green_overlay_backend_wrapper(int a1)
{
  char result; // al

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_face_green_translucent_overlay(a1);
  return result;
}

