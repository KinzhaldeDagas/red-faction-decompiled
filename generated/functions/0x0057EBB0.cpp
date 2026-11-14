// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057EBB0 rf_debug_draw_wire_sphere_backend_dispatch
// UNREALRED VERIFIED [event-item-dispatch-20261028]: If renderer selector0x187CC9C==102 delegates(center,radius,state) to0x5DB200, else returns0. Does not implement sphere geometry itself.
char __cdecl rf_debug_draw_wire_sphere_backend_dispatch(int a1, float a2, int a3)
{
  if ( dword_187CC9C == 102 )
    return rf_debug_draw_wire_sphere_backend_102(a1, a2, a3);
  else
    return 0;
}

