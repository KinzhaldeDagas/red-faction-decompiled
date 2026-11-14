// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF610 rf_jpeg_marker_emit_jfif_app0
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:emit_jfif_app0 matched): EmitsAPP0 FF E0,length16,signatureJFIF NUL,majorBYTE208,minor209,densityunit210,big-endianWORDX/Ydensities212/214,thumbnailwidth0/height0. No thumbnailpixels,inputfieldvalidationorconditionalhere;callercheckswrite_JFIF_header.
int __cdecl rf_jpeg_marker_emit_jfif_app0(int a1)
{
  rf_jpeg_marker_emit_marker((_DWORD *)a1, 224);
  rf_jpeg_marker_emit_2bytes((_DWORD *)a1, 16);
  rf_jpeg_marker_emit_byte((_DWORD *)a1, 74);
  rf_jpeg_marker_emit_byte((_DWORD *)a1, 70);
  rf_jpeg_marker_emit_byte((_DWORD *)a1, 73);
  rf_jpeg_marker_emit_byte((_DWORD *)a1, 70);
  rf_jpeg_marker_emit_byte((_DWORD *)a1, 0);
  rf_jpeg_marker_emit_byte((_DWORD *)a1, *(_BYTE *)(a1 + 208));
  rf_jpeg_marker_emit_byte((_DWORD *)a1, *(_BYTE *)(a1 + 209));
  rf_jpeg_marker_emit_byte((_DWORD *)a1, *(_BYTE *)(a1 + 210));
  rf_jpeg_marker_emit_2bytes((_DWORD *)a1, *(_WORD *)(a1 + 212));
  rf_jpeg_marker_emit_2bytes((_DWORD *)a1, *(_WORD *)(a1 + 214));
  rf_jpeg_marker_emit_byte((_DWORD *)a1, 0);
  return rf_jpeg_marker_emit_byte((_DWORD *)a1, 0);
}

