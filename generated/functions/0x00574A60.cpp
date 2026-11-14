// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574A60 rf_bitmap_get_resolved_file_type
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl(bitmapHandle). Resolves current frame574B80;result-1 returns0,otherwise returns DWORD record+52 file-type code. Does not return pixel-format+60 or animation-kind+56;no header read or normalized boolean. Inherits resolver state mutation and handle validation limitations.
int __cdecl rf_bitmap_get_resolved_file_type(unsigned int handle)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_bitmap_resolve_current_frame_slot(handle);
  if ( v2 == -1 )
    return 0;
  else
    return *(_DWORD *)(dword_1897344 + 108 * v2 + 52);
}

