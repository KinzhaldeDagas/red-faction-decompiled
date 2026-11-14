// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00602320 rf_jpeg_huff_tally_one_block
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:htest_one_block matched): Void(cinfo,s16block64,lastDC,DCfreq257,ACfreq257). CountsDCdifferencecategory(abs),fatal6if>11. ZigzagACindices1..63:tally0xF0foreach16zeroesbeforeanonzero,tally(run<<4)|amplitudecategoryfornonzero,fatal6ifcategory>10;trailingzerosincrementEOB0. DoesnotcountamplitudebitsasHuffmansymbols,setdummyfreq256,updateDCpredictororoutputbytes. Frequencyincrements32-bitlongwithoutoverflowcheck;callerownsarrayclearing.
_DWORD *__cdecl rf_jpeg_huff_tally_one_block(int a1, __int16 *a2, int a3, _DWORD *a4, _DWORD *a5)
{
  _DWORD *result; // eax
  int v6; // eax
  int v7; // [esp+0h] [ebp-10h]
  int j; // [esp+0h] [ebp-10h]
  int v9; // [esp+4h] [ebp-Ch]
  int i; // [esp+8h] [ebp-8h]
  int v11; // [esp+Ch] [ebp-4h]
  int v12; // [esp+Ch] [ebp-4h]

  v11 = *a2 - a3;
  if ( v11 < 0 )
    v11 = a3 - *a2;
  v7 = 0;
  while ( v11 )
  {
    ++v7;
    v11 >>= 1;
  }
  if ( v7 > 11 )
  {
    *(_DWORD *)(*(_DWORD *)a1 + 20) = 6;
    (**(void (__cdecl ***)(int))a1)(a1);
  }
  result = a4;
  ++a4[v7];
  v9 = 0;
  for ( i = 1; i < 64; ++i )
  {
    v6 = dword_648B90[i];
    v12 = a2[v6];
    if ( a2[v6] )
    {
      while ( v9 > 15 )
      {
        ++a5[240];
        v9 -= 16;
      }
      if ( v12 < 0 )
        v12 = -v12;
      for ( j = 1; ; ++j )
      {
        v12 >>= 1;
        if ( !v12 )
          break;
      }
      if ( j > 10 )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 6;
        (**(void (__cdecl ***)(int))a1)(a1);
      }
      result = a5;
      ++a5[16 * v9 + j];
      v9 = 0;
    }
    else
    {
      result = (_DWORD *)++v9;
    }
  }
  if ( v9 > 0 )
  {
    ++*a5;
    return a5;
  }
  return result;
}

