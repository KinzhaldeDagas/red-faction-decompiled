// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00602200 rf_jpeg_huff_encode_mcu_gather
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:encode_mcu_gather matched): Statistics-modeboolean(cinfo,MCUblocks),alwaysTRUE1. Restartintervalboundaryzerosper-scanDCpredictorsandreloadscountdown,thendecrements;NOrestartbytesoutput. Foreachblocks_in_MCU268,MCUmembership272+4*i selectsscancomponent,tallyoneblockintoDCcountptr76+table*4/ACcount92+,updatelastDCpredictor. Doesnotuseoutputbuffer,derivedcodesorbitstate;suspensionunsupported/unnecessaryinstatisticsmode.
int __cdecl rf_jpeg_huff_encode_mcu_gather(_DWORD *a1, int a2)
{
  int i; // [esp+0h] [ebp-10h]
  int v4; // [esp+0h] [ebp-10h]
  int j; // [esp+8h] [ebp-8h]
  int v6; // [esp+Ch] [ebp-4h]

  v6 = a1[90];
  if ( a1[49] )
  {
    if ( !*(_DWORD *)(v6 + 36) )
    {
      for ( i = 0; i < a1[60]; ++i )
        *(_DWORD *)(v6 + 4 * i + 20) = 0;
      *(_DWORD *)(v6 + 36) = a1[49];
    }
    --*(_DWORD *)(v6 + 36);
  }
  for ( j = 0; j < a1[67]; ++j )
  {
    v4 = a1[j + 68];
    rf_jpeg_huff_tally_one_block(
      (int)a1,
      *(__int16 **)(a2 + 4 * j),
      *(_DWORD *)(v6 + 4 * v4 + 20),
      *(_DWORD **)(v6 + 4 * *(_DWORD *)(a1[v4 + 61] + 20) + 76),
      *(_DWORD **)(v6 + 4 * *(_DWORD *)(a1[v4 + 61] + 24) + 92));
    *(_DWORD *)(v6 + 4 * v4 + 20) = **(__int16 **)(a2 + 4 * j);
  }
  return 1;
}

