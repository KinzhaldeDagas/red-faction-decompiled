// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF5B0 rf_jpeg_marker_write_file_header
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:write_file_header matched): EmitsSOI FF D8,setsmarker.last_restart_interval28=0. Ifwrite_JFIF_header204 nonzero,emitAPP0JFIF;thenifwrite_Adobe_marker216 nonzero,emitAPP14Adobe. DoesnotemitDQT/SOF/SOSorimagedata;globalcompressionstateunchanged. Calledimmediatelybycompressorinitializationbeforeapplicationmarkers.
_DWORD *__cdecl rf_jpeg_marker_write_file_header(_DWORD *a1)
{
  _DWORD *result; // eax
  int v2; // [esp+0h] [ebp-4h]

  v2 = a1[86];
  rf_jpeg_marker_emit_marker(a1, 216);
  *(_DWORD *)(v2 + 28) = 0;
  if ( a1[51] )
    rf_jpeg_marker_emit_jfif_app0((int)a1);
  result = a1;
  if ( a1[54] )
    return (_DWORD *)rf_jpeg_marker_emit_adobe_app14(a1);
  return result;
}

