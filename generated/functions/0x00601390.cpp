// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00601390 rf_jpeg_gen_optimal_table
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:jpeg_gen_optimal_table matched): Cdecl(cinfo,Huffmantable,freq257longs),voidAPI. DESTRUCTIVELYmodifiesfreqarray:setsfreq256=1asdummy,initializescodesize257=0,others257=-1. Repeatedlyfindstwoleastnonzero frequencies(initialsearchlimit1000000000,tieschoosehigherindex),mergescountsandlengthchains. Rejectsderivedcodelength>32(error39). Buildsbytecountsbylength,redistributeslengths32..17intolegal<=16usingIJGalgorithm,removesonecodefromlongestremaininglength(dummyall-onesprevention). Copiesbits[0..16]tohtbl,emitsactualsymbol0..255 orderedbyoriginalcodesize1..32 thennumericvalue,huffval+17;sent_table276=0. No frequencyoverflow/negative/capacityvalidation;searchassumesordinarynonnegativecountswithinits1e9sentinel. Doesnotemitbitstreamorbuildderivedencodinglookuphere.
int __cdecl rf_jpeg_gen_optimal_table(int a1, int a2, int a3)
{
  int result; // eax
  int j; // [esp+0h] [ebp-854h]
  int k; // [esp+0h] [ebp-854h]
  _DWORD v6[517]; // [esp+4h] [ebp-850h] BYREF
  int v7; // [esp+818h] [ebp-3Ch]
  int v8; // [esp+81Ch] [ebp-38h]
  int v9; // [esp+820h] [ebp-34h]
  int v10; // [esp+824h] [ebp-30h]
  int v11; // [esp+828h] [ebp-2Ch]
  int v12; // [esp+82Ch] [ebp-28h]
  int v13; // [esp+830h] [ebp-24h]
  int v14; // [esp+834h] [ebp-20h]
  char v15; // [esp+838h] [ebp-1Ch]
  int v16; // [esp+840h] [ebp-14h]
  int v17; // [esp+844h] [ebp-10h]
  int i; // [esp+848h] [ebp-Ch]
  int v19; // [esp+84Ch] [ebp-8h]
  int v20; // [esp+850h] [ebp-4h]

  v7 = 0;
  v8 = 0;
  v9 = 0;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  v13 = 0;
  v14 = 0;
  v15 = 0;
  memset(v6, 0, 0x404u);
  for ( i = 0; i < 257; ++i )
    v6[i + 258] = -1;
  *(_DWORD *)(a3 + 1024) = 1;
  while ( 1 )
  {
    v17 = -1;
    v19 = 1000000000;
    for ( i = 0; i <= 256; ++i )
    {
      if ( *(_DWORD *)(a3 + 4 * i) )
      {
        if ( *(_DWORD *)(a3 + 4 * i) <= v19 )
        {
          v19 = *(_DWORD *)(a3 + 4 * i);
          v17 = i;
        }
      }
    }
    v16 = -1;
    v19 = 1000000000;
    for ( i = 0; i <= 256; ++i )
    {
      if ( *(_DWORD *)(a3 + 4 * i) && *(_DWORD *)(a3 + 4 * i) <= v19 && i != v17 )
      {
        v19 = *(_DWORD *)(a3 + 4 * i);
        v16 = i;
      }
    }
    if ( v16 < 0 )
      break;
    *(_DWORD *)(a3 + 4 * v17) += *(_DWORD *)(a3 + 4 * v16);
    *(_DWORD *)(a3 + 4 * v16) = 0;
    ++v6[v17];
    while ( (int)v6[v17 + 258] >= 0 )
    {
      v17 = v6[v17 + 258];
      ++v6[v17];
    }
    v6[v17 + 258] = v16;
    ++v6[v16];
    while ( (int)v6[v16 + 258] >= 0 )
    {
      v16 = v6[v16 + 258];
      ++v6[v16];
    }
  }
  for ( i = 0; i <= 256; ++i )
  {
    if ( v6[i] )
    {
      if ( (int)v6[i] > 32 )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 39;
        (**(void (__cdecl ***)(int))a1)(a1);
      }
      ++*((_BYTE *)&v7 + v6[i]);
    }
  }
  for ( i = 32; i > 16; --i )
  {
    while ( *((_BYTE *)&v7 + i) )
    {
      for ( j = i - 2; !*((_BYTE *)&v7 + j); --j )
        ;
      *((_BYTE *)&v7 + i) -= 2;
      ++*((_BYTE *)&v6[516] + i + 3);
      *((_BYTE *)&v7 + j + 1) += 2;
      --*((_BYTE *)&v7 + j);
    }
  }
  while ( !*((_BYTE *)&v7 + i) )
    --i;
  --*((_BYTE *)&v7 + i);
  *(_DWORD *)a2 = v7;
  *(_DWORD *)(a2 + 4) = v8;
  result = v9;
  *(_DWORD *)(a2 + 8) = v9;
  *(_DWORD *)(a2 + 12) = v10;
  LOBYTE(result) = v11;
  *(_BYTE *)(a2 + 16) = v11;
  v20 = 0;
  for ( i = 1; i <= 32; ++i )
  {
    for ( k = 0; k <= 255; ++k )
    {
      result = k;
      if ( v6[k] == i )
      {
        LOBYTE(result) = k;
        *(_BYTE *)(v20 + a2 + 17) = k;
        ++v20;
      }
    }
  }
  *(_DWORD *)(a2 + 276) = 0;
  return result;
}

