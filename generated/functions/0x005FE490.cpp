// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FE490 rf_jpeg_alloc_barray
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemmgr.c:alloc_barray matched): Cdecl(cinfo,poolID,blocksPerRow,numRows),returnsblock-row-pointerarray. JBLOCK64signed16coefficients=128bytes. maxrows=999999988/(blocksPerRow*128),nonpositivequotienterror70;zero/overflowed denominator notguardedbeforedivision. Storeschosenrowsperchunk atmanager80,allocates4*numRows pointerbytes andlargechunks ofblocksPerRow*chunkRows*128,setsrowstride128*blocksPerRow. No coefficientzeroing orfull multiplicationoverflowcheck;lastchunkshrinks.
int __cdecl rf_jpeg_alloc_barray(_DWORD *a1, unsigned int a2, int a3, signed int a4)
{
  unsigned int v5; // [esp+0h] [ebp-20h]
  unsigned int v6; // [esp+4h] [ebp-1Ch]
  int v7; // [esp+8h] [ebp-18h]
  int v8; // [esp+Ch] [ebp-14h]
  signed int v9; // [esp+10h] [ebp-10h]
  unsigned int v10; // [esp+14h] [ebp-Ch]
  unsigned int i; // [esp+18h] [ebp-8h]
  _DWORD *v12; // [esp+1Ch] [ebp-4h]

  v7 = a1[1];
  v9 = 0x3B9AC9F4u / (a3 << 7);
  if ( v9 <= 0 )
  {
    *(_DWORD *)(*a1 + 20) = 70;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  if ( v9 >= a4 )
    v10 = a4;
  else
    v10 = 0x3B9AC9F4u / (a3 << 7);
  *(_DWORD *)(v7 + 80) = v10;
  v8 = rf_jpeg_alloc_small(a1, a2, 4 * a4);
  v6 = 0;
  while ( v6 < a4 )
  {
    if ( v10 >= a4 - v6 )
      v5 = a4 - v6;
    else
      v5 = v10;
    v10 = v5;
    v12 = rf_jpeg_alloc_large(a1, a2, (a3 * v5) << 7);
    for ( i = v5; i; --i )
    {
      *(_DWORD *)(v8 + 4 * v6++) = v12;
      v12 += 32 * a3;
    }
  }
  return v8;
}

