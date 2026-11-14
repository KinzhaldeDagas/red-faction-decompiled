// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E950 rf_renderer_oriented_billboard_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Backend187CC9C==102 forwards two DWORDs,float and fourthDWORD to oriented world billboard/aspect renderer;unsupported backend returns byte0. No visibility or geometry work in bridge.
char __cdecl rf_renderer_oriented_billboard_backend_wrapper(int a1, int a2, float a3, int a4)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_oriented_world_billboard_aspect(a1, a2, a3, a4);
  else
    return 0;
}

