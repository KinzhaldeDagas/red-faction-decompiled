// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057EB30 rf_renderer_wire_cylinder_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Backend102 forwards center/orientation DWORDs,radius float,full-height float,stateDWORD to16-segment wire-cylinder renderer;unsupported returns byte0. Does not generate rings or change current color locally.
char __cdecl rf_renderer_wire_cylinder_backend_wrapper(int a1, int a2, float a3, float a4, int a5)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_wire_cylinder_16_segments(a1, a2, a3, a4, a5);
  else
    return 0;
}

