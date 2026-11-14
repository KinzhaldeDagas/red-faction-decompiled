// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FCFD0 rf_jpeg_set_quality
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcparam.c:jpeg_set_quality matched): Cdecl(cinfo,quality,forceBaseline):quality_scaling0x5FCF80 then set_linear_quality0x5FCF40. Mutates/reallocates quant tables0/1 via helpers,does not set othercompression parameters orwriteoutput. APIvoid.
_DWORD *__cdecl rf_jpeg_set_quality(_DWORD *a1, int a2, int a3)
{
  int v4; // [esp+Ch] [ebp+Ch]

  v4 = rf_jpeg_quality_scaling(a2);
  return rf_jpeg_set_linear_quality(a1, v4, a3);
}

