// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057FC90 rf_renderer_polyline_ribbon_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Backend102 forwards twoDWORD arguments to textured polyline-ribbon renderer;otherwise byte0. Does not allocate path data or check point count in this bridge.
char __cdecl rf_renderer_polyline_ribbon_backend_wrapper(int a1, int a2)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_textured_polyline_ribbon(a1, a2);
  else
    return 0;
}

