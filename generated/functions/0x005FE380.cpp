// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FE380 rf_jpeg_alloc_sarray
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemmgr.c:alloc_sarray matched): Cdecl(cinfo,poolID,samplesPerRow,numRows),returnsrow-pointerarray. Computesmaxrowsperchunk=999999988/samplesPerRow;nonpositivequotienterror70WidthOverflow. samplesPerRow0 causesintegerdivide beforethatcheck. Chooseschunkrows=min(maxrows,numRows),storesmanager.last_rowsperchunk80. Allocates4*numRows pointerbytes viaalloc_small,thenlargechunks ofsamplesPerRow*chunkRows bytes,setsrowpointers at byte stridesamplesPerRow. Shrinkslastchunk tonecessaryrows. No pixelzeroing orvalidation ofnumRows/32-bitmultiplicationoverflow.
int __cdecl rf_jpeg_alloc_sarray(_DWORD *a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
  unsigned int v5; // [esp+0h] [ebp-20h]
  unsigned int v6; // [esp+4h] [ebp-1Ch]
  int v7; // [esp+8h] [ebp-18h]
  int v8; // [esp+Ch] [ebp-14h]
  unsigned int v9; // [esp+14h] [ebp-Ch]
  unsigned int i; // [esp+18h] [ebp-8h]
  _DWORD *v11; // [esp+1Ch] [ebp-4h]

  v7 = a1[1];
  if ( (int)(0x3B9AC9F4 / a3) <= 0 )
  {
    *(_DWORD *)(*a1 + 20) = 70;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  if ( (int)(0x3B9AC9F4 / a3) >= (int)a4 )
    v9 = a4;
  else
    v9 = 0x3B9AC9F4 / a3;
  *(_DWORD *)(v7 + 80) = v9;
  v8 = rf_jpeg_alloc_small(a1, a2, 4 * a4);
  v6 = 0;
  while ( v6 < a4 )
  {
    if ( v9 >= a4 - v6 )
      v5 = a4 - v6;
    else
      v5 = v9;
    v9 = v5;
    v11 = rf_jpeg_alloc_large(a1, a2, a3 * v5);
    for ( i = v5; i; --i )
    {
      *(_DWORD *)(v8 + 4 * v6++) = v11;
      v11 = (_DWORD *)((char *)v11 + a3);
    }
  }
  return v8;
}

