// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E9D0 rf_renderer_world_billboard_rectangle_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Backend102 forwards position pointer,three floats,and packed-state DWORD to world-billboard rectangle renderer;otherwise byte0. No local clamp/cull or texture/state setup.
char __cdecl rf_renderer_world_billboard_rectangle_backend_wrapper(float *a1, float a2, float a3, float a4, int a5)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_world_billboard_rectangle(a1, a2, a3, a4, a5);
  else
    return 0;
}

