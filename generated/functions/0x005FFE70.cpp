// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FFE70 rf_jpeg_marker_emit_dri
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:emit_dri matched): EmitsDRI FF DD,fixedlength4,thenbig-endianlow16bits ofrestart_interval196. No rangecheck orcacheupdatehere;write_scan_headertracks lastvalue. Interval0 explicitlydisablespriorrestartsetting.
int __cdecl rf_jpeg_marker_emit_dri(_DWORD *a1)
{
  rf_jpeg_marker_emit_marker(a1, 221);
  rf_jpeg_marker_emit_2bytes(a1, 4);
  return rf_jpeg_marker_emit_2bytes(a1, a1[49]);
}

