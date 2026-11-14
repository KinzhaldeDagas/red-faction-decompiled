// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580460 rf_renderer_face_wire_outline_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Backend102 forwards two DWORD arguments to verified face-wire outline renderer;otherwise returns void without drawing. No local loop or renderer-state setup.
void __cdecl rf_renderer_face_wire_outline_backend_wrapper(int a1, int a2)
{
  if ( dword_187CC9C == 102 )
    rf_renderer_draw_face_wire_outline(a1, a2);
}

