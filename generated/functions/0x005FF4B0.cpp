// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF4B0 rf_jpeg_marker_emit_marker
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:emit_marker matched): Cdecl(cinfo,intmark). Emitsbyte255,thenlow8bits ofmark via0x5FF4E0. No markerkind/statecheck,lengthwordorbyte-stuffing. VoidAPI;incidentalcallbackreturn.
int __cdecl rf_jpeg_marker_emit_marker(_DWORD *a1, char a2)
{
  rf_jpeg_marker_emit_byte(a1, 255);
  return rf_jpeg_marker_emit_byte(a1, a2);
}

