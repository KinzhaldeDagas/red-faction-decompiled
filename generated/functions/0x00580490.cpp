// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580490 rf_renderer_submit_textured_world_polygon_color4_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Backend102 forwards bitmap, vertex count, contiguous XYZ array, UV array, mode and four bytes from color pointer to rf_renderer_submit_textured_world_polygon_rgba. Other backends return0. Used by oriented world-font glyph quads. Does not validate color/array pointers or perform layout/clipping itself.
char __cdecl rf_renderer_submit_textured_world_polygon_color4_dispatch(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        char *a6)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_submit_textured_world_polygon_rgba(a1, a2, a3, a4, a5, *a6, a6[1], a6[2], a6[3]);
  else
    return 0;
}

