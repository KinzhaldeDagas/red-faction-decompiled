// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00577AC0 rf_bitmap_load_pcx_cpu_pixels_by_slot
// UNREALRED VERIFIED [bitmap-decoders-20261028]: Argument ordinary bitmap slot INDEX. Allocates format-bytes-per-pixel * record pixelcount+48 into pixel pointer+72; if format+60==1 also allocates768-byte palette+80. Calls PCX decoder0x5E6470(record name,pixels,palette,source context+100), returns true exactly when decoder returns0. No allocation check, existing pointer release or cleanup on decoder failure; failed allocations/partial pixels remain in record.
bool __cdecl rf_bitmap_load_pcx_cpu_pixels_by_slot(int a1)
{
  int v2; // [esp+8h] [ebp-8h]
  int v3; // [esp+Ch] [ebp-4h]

  v2 = dword_1897344 + 108 * a1;
  v3 = rf_bitmap_format_bytes_per_pixel(*(_DWORD *)(v2 + 60));
  *(_DWORD *)(v2 + 72) = operator new(v3 * *(_DWORD *)(v2 + 48));
  if ( *(_DWORD *)(v2 + 60) == 1 )
    *(_DWORD *)(v2 + 80) = operator new(0x300u);
  return rf_pcx_read_indexed8_pixels_palette(
           (char *)(dword_1897344 + 108 * a1),
           *(_BYTE **)(v2 + 72),
           *(void **)(v2 + 80),
           *(_DWORD *)(v2 + 100)) == 0;
}

