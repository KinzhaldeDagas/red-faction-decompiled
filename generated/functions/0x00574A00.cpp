// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574A00 rf_bitmap_format_bits_per_pixel
// UNREALRED VERIFIED [texture-upload-20261028]: Returns8*0x574990(formatcode). Unknowncode defaults8bits; noactualbitmapquery.
int __cdecl rf_bitmap_format_bits_per_pixel(int a1)
{
  return 8 * rf_bitmap_format_bytes_per_pixel(a1);
}

