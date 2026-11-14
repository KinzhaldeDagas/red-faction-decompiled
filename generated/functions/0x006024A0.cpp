// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006024A0 rf_jpeg_huff_finish_pass_gather
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:finish_pass_gather matched): Forcurrent-scancomponents,maintainslocal4-entryDC/ACdoneflags sosharedtableindexoptimizedONCE. AllocatesmissingpermanentHuffmantablesvia0x5FF3A0,thenjpeg_gen_optimal_table oncorresponding257-entryfreqarray. Generatorconsumesfrequencycountsandclearssent_table;derivedcodegenerationoccursduringlateroutputpassstart. No bitstream/EOIemissionorstatechange;indicesassumedvalidatedstartpass. Voidcallback.
int __cdecl rf_jpeg_huff_finish_pass_gather(int a1)
{
  int result; // eax
  int v2; // eax
  int v3; // eax
  _DWORD v4[4]; // [esp+0h] [ebp-38h] BYREF
  int v5; // [esp+10h] [ebp-28h]
  int i; // [esp+14h] [ebp-24h]
  int v7; // [esp+18h] [ebp-20h]
  int *v8; // [esp+1Ch] [ebp-1Ch]
  _DWORD v9[4]; // [esp+20h] [ebp-18h] BYREF
  int v10; // [esp+30h] [ebp-8h]
  int v11; // [esp+34h] [ebp-4h]

  v10 = *(_DWORD *)(a1 + 360);
  memset(v4, 0, sizeof(v4));
  memset(v9, 0, sizeof(v9));
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= *(_DWORD *)(a1 + 240) )
      break;
    v7 = *(_DWORD *)(a1 + 4 * i + 244);
    v5 = *(_DWORD *)(v7 + 20);
    v11 = *(_DWORD *)(v7 + 24);
    if ( !v4[v5] )
    {
      v8 = (int *)(a1 + 4 * v5 + 84);
      if ( !*v8 )
      {
        v2 = rf_jpeg_alloc_huff_table(a1);
        *v8 = v2;
      }
      rf_jpeg_gen_optimal_table(a1, *v8, *(_DWORD *)(v10 + 4 * v5 + 76));
      v4[v5] = 1;
    }
    if ( !v9[v11] )
    {
      v8 = (int *)(a1 + 4 * v11 + 100);
      if ( !*v8 )
      {
        v3 = rf_jpeg_alloc_huff_table(a1);
        *v8 = v3;
      }
      rf_jpeg_gen_optimal_table(a1, *v8, *(_DWORD *)(v10 + 4 * v11 + 92));
      v9[v11] = 1;
    }
  }
  return result;
}

