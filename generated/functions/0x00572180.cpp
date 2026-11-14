// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00572180 rf_bitmap_blit_subrectangle_backend_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Twelve-argument forwarding wrapper: for backend102 calls backend blitter with bitmap, destination rectangle, source rectangle, two flip bytes and render mode unchanged. Does no local clipping, scaling computation or bitmap validation. Other backends do nothing.
void __cdecl rf_bitmap_blit_subrectangle_backend_dispatch(
        unsigned int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        char a10,
        char a11,
        int a12)
{
  if ( dword_187CC9C == 102 )
    rf_renderer_blit_bitmap_subrectangle_backend_102(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
}

