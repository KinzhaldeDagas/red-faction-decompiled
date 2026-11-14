// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF590 rf_jpeg_marker_write_marker_byte
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:write_marker_byte matched): Markerwriter callbackcdecl(cinfo,intval),directwrapper toemit_byte0x5FF4E0. No payloadlength/statecheck orstuffing. Used bypublicpiecemeal markerAPI andcachedwrite_marker loop;voidAPI.
int __cdecl rf_jpeg_marker_write_marker_byte(_DWORD *a1, char a2)
{
  return rf_jpeg_marker_emit_byte(a1, a2);
}

