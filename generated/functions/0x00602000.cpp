// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00602000 rf_jpeg_huff_emit_restart
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:emit_restart matched): Boolean(workingState,restartNum). Firstflush_bitspaddingones;FALSEpropagates. WritesrawFFthenlowBYTE(0xD0+restartNum),checkingbufferflushaftereach;markerbytesareNOTFF00-stuffed. AftersuccessclearsworkingDCpredictors16+4*i forallcomps_in_scan240. Doesnotmodifyentropyrestartcountdown/nextnumber;callercommitmanagesthose. No restartNumrangecheckhere;callersuse0..7.
int __cdecl rf_jpeg_huff_emit_restart(_DWORD *a1, char a2)
{
  int i; // [esp+0h] [ebp-4h]

  if ( !rf_jpeg_huff_flush_bits((int)a1) )
    return 0;
  *(_BYTE *)(*a1)++ = -1;
  if ( --a1[1] || rf_jpeg_huff_dump_buffer(a1) )
  {
    *(_BYTE *)(*a1)++ = a2 - 48;
    if ( --a1[1] || rf_jpeg_huff_dump_buffer(a1) )
    {
      for ( i = 0; i < *(_DWORD *)(a1[8] + 240); ++i )
        a1[i + 4] = 0;
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

