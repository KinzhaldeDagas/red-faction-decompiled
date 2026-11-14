// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E740 rf_debug_draw_world_line_backend_dispatch
// UNREALRED VERIFIED [event-item-dispatch-20261028]: If renderer selector0x187CC9C==102 delegates(two world-space points,packed state) to0x5D9740, else returns0. Called by oriented-wire-box edge emitter.
char __cdecl rf_debug_draw_world_line_backend_dispatch(float *a1, float *a2, int a3)
{
  if ( dword_187CC9C == 102 )
    return rf_debug_draw_world_line_backend_102(a1, a2, a3);
  else
    return 0;
}

