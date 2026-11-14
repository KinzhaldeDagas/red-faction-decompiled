// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574A20 rf_bitmap_get_resolved_size_field96
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl(bitmapHandle). Resolves current frame through574B80;exact result-1 returns-1,otherwise returns DWORD at108B record+96. This is stored-size metadata,not CPU pixel pointer+72 or auxiliary pointer+80,not a fresh sum of mip pixels. Resolver can mutate animation state/global last index. No full-handle generation,occupancy or file-type validation beyond result==-1.
int __cdecl rf_bitmap_get_resolved_size_field96(unsigned int handle)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_bitmap_resolve_current_frame_slot(handle);
  if ( v2 == -1 )
    return -1;
  else
    return *(_DWORD *)(dword_1897344 + 108 * v2 + 96);
}

