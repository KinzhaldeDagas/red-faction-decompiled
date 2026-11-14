// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E3880 rf_renderer_bitmap_get_texture_tile_count
// UNREALRED VERIFIED [renderer-polygons-20261028]: Resolves bitmap/frame through0x574B80,uses16-byte renderer descriptor at0x1E01548+16*index,and returns SIGNED16-bit count at+4. No failed-index or descriptor-pointer checks. Resolver can update animation state,so query is not necessarily side-effect-free.
int __cdecl rf_renderer_bitmap_get_texture_tile_count(unsigned int a1)
{
  return *((__int16 *)dword_1E01548 + 8 * rf_bitmap_resolve_current_frame_slot(a1) + 2);
}

