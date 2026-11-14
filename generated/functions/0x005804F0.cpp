// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005804F0 rf_renderer_solid_wire_outlines_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Backend102 forwards solid pointer DWORD to verified solid-face wire-outline renderer;otherwise no draw and returns backend value. No face filtering performed by bridge.
int __cdecl rf_renderer_solid_wire_outlines_backend_wrapper(int a1)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_solid_face_wire_outlines(a1);
  return result;
}

