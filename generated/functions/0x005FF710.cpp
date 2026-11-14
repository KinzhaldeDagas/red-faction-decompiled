// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF710 rf_jpeg_marker_emit_adobe_app14
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:emit_adobe_app14 matched): EmitsAPP14 FF EE,length14,ASCIIAdobe,version100(two-byte),flags0/0(two-byteeach). Transformbyte=1 forjpeg_color_space60==YCbCr3,2forYCCK5,otherwise0. No colorconversion orimagepayload;callercheckswrite_Adobe_marker.
int __cdecl rf_jpeg_marker_emit_adobe_app14(_DWORD *a1)
{
  int v2; // [esp+0h] [ebp-4h]

  rf_jpeg_marker_emit_marker(a1, 238);
  rf_jpeg_marker_emit_2bytes(a1, 14);
  rf_jpeg_marker_emit_byte(a1, 65);
  rf_jpeg_marker_emit_byte(a1, 100);
  rf_jpeg_marker_emit_byte(a1, 111);
  rf_jpeg_marker_emit_byte(a1, 98);
  rf_jpeg_marker_emit_byte(a1, 101);
  rf_jpeg_marker_emit_2bytes(a1, 100);
  rf_jpeg_marker_emit_2bytes(a1, 0);
  rf_jpeg_marker_emit_2bytes(a1, 0);
  v2 = a1[15];
  if ( v2 == 3 )
    return rf_jpeg_marker_emit_byte(a1, 1);
  if ( v2 == 5 )
    return rf_jpeg_marker_emit_byte(a1, 2);
  return rf_jpeg_marker_emit_byte(a1, 0);
}

