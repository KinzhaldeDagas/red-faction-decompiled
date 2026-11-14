// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00601C10 rf_jpeg_huff_encode_one_block
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:encode_one_block matched): Localboolean(workingState,s16coeffs64,lastDC,derivedDC,derivedAC). EmitsHuffmancategoryofabs(coeff0-lastDC),thenamplitudebits;negativedifferencedecrementedbeforemasktogiveJPEGnegativebitrepresentation. DCcategory>11fatal6 BadDCTCoefficient. ACwalksindices1..63viaoriginalzigzag0x648B90,countszeroes;forruns>15beforeanonzero emitsZRLsymbol0xF0 repeatedly. Nonzerocategory>10fatal6;emitACsymbol(run<<4)|category,thenamplitude(negativevalue-1). Trailingzero runemitsEOB0. Everyemit_bitsfailurepropagatesFALSE;TRUEafterblock. DoesnotupdatepersistentDCpredictor,cinfooutputpositionorrestartcountersitself.
BOOL __cdecl rf_jpeg_huff_encode_one_block(int a1, __int16 *a2, int a3, int a4, int a5)
{
  int v6; // eax
  int v7; // [esp+0h] [ebp-18h]
  int j; // [esp+0h] [ebp-18h]
  int v9; // [esp+4h] [ebp-14h]
  int i; // [esp+8h] [ebp-10h]
  int v11; // [esp+Ch] [ebp-Ch]
  int v12; // [esp+Ch] [ebp-Ch]
  int v13; // [esp+10h] [ebp-8h]
  int v14; // [esp+10h] [ebp-8h]

  v11 = *a2 - a3;
  v13 = v11;
  if ( v11 < 0 )
  {
    v13 = a3 - *a2;
    --v11;
  }
  v7 = 0;
  while ( v13 )
  {
    ++v7;
    v13 >>= 1;
  }
  if ( v7 > 11 )
  {
    *(_DWORD *)(**(_DWORD **)(a1 + 32) + 20) = 6;
    (***(void (__cdecl ****)(_DWORD))(a1 + 32))(*(_DWORD *)(a1 + 32));
  }
  if ( !rf_jpeg_huff_emit_bits(a1, *(_DWORD *)(a4 + 4 * v7), *(char *)(v7 + a4 + 1024)) )
    return 0;
  if ( v7 && !rf_jpeg_huff_emit_bits(a1, v11, v7) )
    return 0;
  v9 = 0;
  for ( i = 1; i < 64; ++i )
  {
    v6 = dword_648B90[i];
    v14 = a2[v6];
    if ( a2[v6] )
    {
      while ( v9 > 15 )
      {
        if ( !rf_jpeg_huff_emit_bits(a1, *(_DWORD *)(a5 + 960), *(char *)(a5 + 1264)) )
          return 0;
        v9 -= 16;
      }
      v12 = v14;
      if ( v14 < 0 )
      {
        v14 = -v14;
        --v12;
      }
      for ( j = 1; ; ++j )
      {
        v14 >>= 1;
        if ( !v14 )
          break;
      }
      if ( j > 10 )
      {
        *(_DWORD *)(**(_DWORD **)(a1 + 32) + 20) = 6;
        (***(void (__cdecl ****)(_DWORD))(a1 + 32))(*(_DWORD *)(a1 + 32));
      }
      if ( !rf_jpeg_huff_emit_bits(a1, *(_DWORD *)(a5 + 4 * (j + 16 * v9)), *(char *)(j + 16 * v9 + a5 + 1024)) )
        return 0;
      if ( !rf_jpeg_huff_emit_bits(a1, v12, j) )
        return 0;
      v9 = 0;
    }
    else
    {
      ++v9;
    }
  }
  return v9 <= 0 || rf_jpeg_huff_emit_bits(a1, *(_DWORD *)a5, *(char *)(a5 + 1024));
}

