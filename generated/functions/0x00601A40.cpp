// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00601A40 rf_jpeg_huff_encode_mcu
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:encode_mcu_huff matched): Boolean(cinfo,MCUblockpointerarray). Builds36-byteLOCALworkingstate:nextByte0/free4 fromdest24,savedputbuffer8/putbits12/DCpredictors16..31 fromentropyobject12..35,cinfo32. Ifrestartintervalenabledandcountdown0,emit_restart usingcurrentRSTnumber;FALSEreturn0. Forblocks0..blocks_in_MCU268-1,MCUmembership272+4*i selects scancomponent,encode_one_block withthatcomponentDCpredictorandderivedDC/ACtables;onFALSEreturns0withoutcommittinglocalworkingfields. SuccessupdateslocalDCtoactualblockDC,thencommitsdestpointer/freeandentropybitstate/predictors. Restartboundaryreloadscountdown,advancesRSTnumbermod8,decrementscountdown. Externalbufferflushmayalreadyhaveoccurred;notanI/Orollbackguarantee.
int __cdecl rf_jpeg_huff_encode_mcu(int a1, int a2)
{
  _DWORD *v3; // eax
  int v4; // [esp+0h] [ebp-34h] BYREF
  int v5; // [esp+4h] [ebp-30h]
  int v6; // [esp+8h] [ebp-2Ch]
  int v7; // [esp+Ch] [ebp-28h]
  int v8; // [esp+10h] [ebp-24h]
  int v9; // [esp+14h] [ebp-20h]
  int v10; // [esp+18h] [ebp-1Ch]
  int v11; // [esp+1Ch] [ebp-18h]
  int v12; // [esp+20h] [ebp-14h]
  int v13; // [esp+24h] [ebp-10h]
  int v14; // [esp+28h] [ebp-Ch]
  int i; // [esp+2Ch] [ebp-8h]
  _DWORD *v16; // [esp+30h] [ebp-4h]

  v16 = *(_DWORD **)(a1 + 360);
  v4 = **(_DWORD **)(a1 + 24);
  v5 = *(_DWORD *)(*(_DWORD *)(a1 + 24) + 4);
  v6 = v16[3];
  v7 = v16[4];
  v8 = v16[5];
  v9 = v16[6];
  v10 = v16[7];
  v11 = v16[8];
  v12 = a1;
  if ( *(_DWORD *)(a1 + 196) && !v16[9] && !rf_jpeg_huff_emit_restart(&v4, v16[10]) )
    return 0;
  for ( i = 0; i < *(_DWORD *)(a1 + 268); ++i )
  {
    v13 = *(_DWORD *)(a1 + 4 * i + 272);
    v14 = *(_DWORD *)(a1 + 4 * v13 + 244);
    if ( !rf_jpeg_huff_encode_one_block(
            (int)&v4,
            *(__int16 **)(a2 + 4 * i),
            *(&v8 + v13),
            v16[*(_DWORD *)(v14 + 20) + 11],
            v16[*(_DWORD *)(v14 + 24) + 15]) )
      return 0;
    *(&v8 + v13) = **(__int16 **)(a2 + 4 * i);
  }
  **(_DWORD **)(a1 + 24) = v4;
  *(_DWORD *)(*(_DWORD *)(a1 + 24) + 4) = v5;
  v3 = v16 + 3;
  v16[3] = v6;
  v3[1] = v7;
  v3[2] = v8;
  v3[3] = v9;
  v3[4] = v10;
  v3[5] = v11;
  if ( *(_DWORD *)(a1 + 196) )
  {
    if ( !v16[9] )
    {
      v16[9] = *(_DWORD *)(a1 + 196);
      ++v16[10];
      v16[10] &= 7u;
    }
    --v16[9];
  }
  return 1;
}

