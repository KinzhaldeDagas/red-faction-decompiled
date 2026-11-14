// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600030 rf_jpeg_marker_write_tables_only
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:write_tables_only matched): EmitsSOI,thenallnonnull4quanttablesusingDQTsentflags. Ifnotarithmetic,emitsallnonnull4DC/4ACDHTtablesrespectingsentflags;arithskipsHuffmantablesbutdoesNOTemitDACstubhere. EmitsEOI. NoAPP0/APP14,SOF/SOSorimagedata. Callerpublicjpeg_write_tableshandlesdestinationinit/term;noabort/freehere.
int __cdecl rf_jpeg_marker_write_tables_only(_DWORD *a1)
{
  int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]

  rf_jpeg_marker_emit_marker(a1, 216);
  for ( i = 0; i < 4; ++i )
  {
    if ( a1[i + 17] )
      rf_jpeg_marker_emit_dqt(a1, i);
  }
  if ( !a1[44] )
  {
    for ( j = 0; j < 4; ++j )
    {
      if ( a1[j + 21] )
        rf_jpeg_marker_emit_dht(a1, j, 0);
      if ( a1[j + 25] )
        rf_jpeg_marker_emit_dht(a1, j, 1);
    }
  }
  return rf_jpeg_marker_emit_marker(a1, 217);
}

