// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057EAA0 rf_renderer_camera_facing_beam_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Backend102 forwards endpoint pointers,width float,and stateDWORD to camera-facing beam renderer;unsupported returns byte0. Does not independently normalize endpoints or build vertices.
char __cdecl rf_renderer_camera_facing_beam_backend_wrapper(float *a1, float *a2, float a3, int a4)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_camera_facing_beam_quad(a1, a2, a3, a4);
  else
    return 0;
}

