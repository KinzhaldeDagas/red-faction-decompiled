// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FCF40 rf_jpeg_set_linear_quality
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcparam.c:jpeg_set_linear_quality matched): Cdecl(cinfo,scaleFactor,forceBaseline). Adds quant table0 from original64-entry luminance constants0x647440,table1 chrominance0x647340 using same percentage scaling/clamping. Does not convert user quality toscale;statevalidation delegated add_quant_table. APIvoid.
_DWORD *__cdecl rf_jpeg_set_linear_quality(_DWORD *a1, int a2, int a3)
{
  rf_jpeg_add_quant_table(a1, 0, (int)&unk_647440, a2, a3);
  return rf_jpeg_add_quant_table(a1, 1u, (int)&unk_647340, a2, a3);
}

