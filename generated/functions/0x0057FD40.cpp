// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057FD40 rf_renderer_midpoint_arrow_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Backend102 forwards six scalar endpoint floats and three colorDWORDs to debug midpoint-arrow renderer;otherwise void no-op. Distinct from endpoint-arrow bridge57FDA0;no global color restore/geometry here.
void __cdecl rf_renderer_midpoint_arrow_backend_wrapper(
        float a1,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6,
        int a7,
        int a8,
        int a9)
{
  if ( dword_187CC9C == 102 )
    rf_renderer_draw_debug_midpoint_arrow(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

