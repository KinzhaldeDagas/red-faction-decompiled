// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00603DE0 rf_jpeg_downsample_fullsize_smooth
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcsample.c:fullsize_smooth_downsample matched): Full-size 3x3 smoothing. Requires one context row above and below and pads their right edges. Center weight is 65536-512*S; each of eight neighbors has weight 64*S. Adds 32768 and shifts by 16 into a byte. Uses rolling column sums and replicates horizontal edges. Does not downsample or explicitly clamp S.
int __cdecl rf_jpeg_downsample_fullsize_smooth(int *a1, int a2, int a3, int a4)
{
  int result; // eax
  unsigned __int8 *v5; // [esp+0h] [ebp-38h]
  unsigned __int8 *v6; // [esp+0h] [ebp-38h]
  int v7; // [esp+4h] [ebp-34h]
  int v8; // [esp+8h] [ebp-30h]
  int v9; // [esp+8h] [ebp-30h]
  _BYTE *v10; // [esp+Ch] [ebp-2Ch]
  _BYTE *v11; // [esp+Ch] [ebp-2Ch]
  int v12; // [esp+10h] [ebp-28h]
  int v13; // [esp+14h] [ebp-24h]
  int i; // [esp+1Ch] [ebp-1Ch]
  unsigned __int8 *v15; // [esp+20h] [ebp-18h]
  unsigned __int8 *v16; // [esp+20h] [ebp-18h]
  int v17; // [esp+24h] [ebp-14h]
  int v18; // [esp+24h] [ebp-14h]
  int j; // [esp+28h] [ebp-10h]
  unsigned __int8 *v20; // [esp+2Ch] [ebp-Ch]
  unsigned __int8 *v21; // [esp+2Ch] [ebp-Ch]
  int v22; // [esp+30h] [ebp-8h]
  int v23; // [esp+30h] [ebp-8h]
  int v24; // [esp+34h] [ebp-4h]

  v13 = 8 * *(_DWORD *)(a2 + 28);
  rf_jpeg_downsample_expand_right_edge(a3 - 4, a1[58] + 2, a1[7], v13);
  v24 = 0x10000 - (a1[47] << 9);
  v7 = a1[47] << 6;
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= *(_DWORD *)(a2 + 12) )
      break;
    v10 = *(_BYTE **)(a4 + 4 * i);
    v15 = *(unsigned __int8 **)(a3 + 4 * i);
    v5 = *(unsigned __int8 **)(a3 + 4 * i - 4);
    v20 = *(unsigned __int8 **)(a3 + 4 * i + 4);
    v17 = *v15 + *v20 + *v5;
    v21 = v20 + 1;
    v6 = v5 + 1;
    v22 = *v15;
    v16 = v15 + 1;
    v8 = *v16 + *v21 + *v6;
    *v10 = (unsigned int)(v7 * (v8 + v17 + v17 - v22) + v24 * v22 + 0x8000) >> 16;
    v11 = v10 + 1;
    v12 = v17;
    v18 = v8;
    for ( j = v13 - 2; j; --j )
    {
      v23 = *v16++;
      v9 = *v16 + *++v21 + *++v6;
      *v11++ = (unsigned int)(v7 * (v9 + v12 + v18 - v23) + v24 * v23 + 0x8000) >> 16;
      v12 = v18;
      v18 = v9;
    }
    *v11 = (v7 * (v18 + v12 + v18 - *v16) + v24 * (unsigned int)*v16 + 0x8000) >> 16;
  }
  return result;
}

