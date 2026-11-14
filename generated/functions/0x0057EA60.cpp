// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057EA60 rf_renderer_padded_beam_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Backend102 forwards twoDWORDs,float,and stateDWORD to camera-plane padded beam renderer;other backends no call,returns void. No local clipping or line-plane correction.
void __cdecl rf_renderer_padded_beam_backend_wrapper(int a1, int a2, float a3, int a4)
{
  if ( dword_187CC9C == 102 )
    rf_renderer_draw_camera_plane_beam_quad_padded(a1, a2, a3, a4);
}

