// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E38B0 rf_renderer_bitmap_get_texture_tile_rectangle
// UNREALRED VERIFIED [renderer-polygons-20261028]: Resolves bitmap/frame via0x574B80,loads renderer descriptor+12 tile-array pointer. Tile records32bytes; copies DWORD fields+16/+20/+24/+28 to caller outputs x,y,width,height. Returns fourth output pointer. No index,negative frame/tile or output-pointer checks. Resolver can mutate animation state.
_DWORD *__cdecl rf_renderer_bitmap_get_texture_tile_rectangle(
        unsigned int a1,
        int a2,
        _DWORD *a3,
        _DWORD *a4,
        _DWORD *a5,
        _DWORD *a6)
{
  char *v7; // [esp+0h] [ebp-8h]

  v7 = (char *)dword_1E01548 + 16 * rf_bitmap_resolve_current_frame_slot(a1);
  *a3 = *(_DWORD *)(*((_DWORD *)v7 + 3) + 32 * a2 + 16);
  *a4 = *(_DWORD *)(*((_DWORD *)v7 + 3) + 32 * a2 + 20);
  *a5 = *(_DWORD *)(*((_DWORD *)v7 + 3) + 32 * a2 + 24);
  *a6 = *(_DWORD *)(*((_DWORD *)v7 + 3) + 32 * a2 + 28);
  return a6;
}

