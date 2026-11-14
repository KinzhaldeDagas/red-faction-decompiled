// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00603A50 rf_jpeg_downsample_h2v2_smooth
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcsample.c:h2v2_smooth_downsample matched): Integrated 2x2 downsampling and smoothing. Requires one context row above and below; right-pads rows -1..max_v to twice output width. With S=smoothing_factor, each central 2x2 pixel has weight 16384-80*S, four outer corner pixels have weight 16*S, and eight outer edge pixels have weight 32*S. Adds 32768 and shifts by 16 into a byte. Horizontal edges are replicated. No explicit S clamp.
int __cdecl rf_jpeg_downsample_h2v2_smooth(_DWORD *a1, int a2, int a3, int a4)
{
  int result; // eax
  unsigned __int8 *v5; // [esp+0h] [ebp-34h]
  unsigned __int8 *v6; // [esp+0h] [ebp-34h]
  int v7; // [esp+4h] [ebp-30h]
  int v8; // [esp+8h] [ebp-2Ch]
  _BYTE *v9; // [esp+Ch] [ebp-28h]
  _BYTE *v10; // [esp+Ch] [ebp-28h]
  unsigned __int8 *v11; // [esp+10h] [ebp-24h]
  unsigned __int8 *v12; // [esp+10h] [ebp-24h]
  int v13; // [esp+14h] [ebp-20h]
  int i; // [esp+1Ch] [ebp-18h]
  int j; // [esp+20h] [ebp-14h]
  unsigned __int8 *v16; // [esp+24h] [ebp-10h]
  unsigned __int8 *v17; // [esp+24h] [ebp-10h]
  unsigned __int8 *v18; // [esp+28h] [ebp-Ch]
  unsigned __int8 *v19; // [esp+28h] [ebp-Ch]
  int v20; // [esp+30h] [ebp-4h]

  v13 = 8 * *(_DWORD *)(a2 + 28);
  rf_jpeg_downsample_expand_right_edge(a3 - 4, a1[58] + 2, a1[7], 16 * *(_DWORD *)(a2 + 28));
  v20 = 0x4000 - 80 * a1[47];
  v8 = 16 * a1[47];
  v7 = 0;
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= *(_DWORD *)(a2 + 12) )
      break;
    v9 = *(_BYTE **)(a4 + 4 * i);
    v18 = *(unsigned __int8 **)(a3 + 4 * v7);
    v11 = *(unsigned __int8 **)(a3 + 4 * v7 + 4);
    v5 = *(unsigned __int8 **)(a3 + 4 * v7 - 4);
    v16 = *(unsigned __int8 **)(a3 + 4 * v7 + 8);
    *v9 = (v8 * (*v16 + v5[2] + *v5 + 2 * (v11[2] + *v11 + v18[2] + *v18 + v16[1] + *v16 + v5[1] + *v5) + v16[2])
         + v20 * (v11[1] + *v11 + v18[1] + (unsigned int)*v18)
         + 0x8000) >> 16;
    v10 = v9 + 1;
    v19 = v18 + 2;
    v12 = v11 + 2;
    v6 = v5 + 2;
    v17 = v16 + 2;
    for ( j = v13 - 2; j; --j )
    {
      *v10++ = (v8
              * (*(v17 - 1)
               + v6[2]
               + *(v6 - 1)
               + 2 * (v12[2] + *(v12 - 1) + v19[2] + *(v19 - 1) + v17[1] + *v17 + v6[1] + *v6)
               + v17[2])
              + v20 * (v12[1] + *v12 + v19[1] + (unsigned int)*v19)
              + 0x8000) >> 16;
      v19 += 2;
      v12 += 2;
      v6 += 2;
      v17 += 2;
    }
    *v10 = (v8
          * (*(v17 - 1)
           + v6[1]
           + *(v6 - 1)
           + 2 * (v12[1] + *(v12 - 1) + v19[1] + *(v19 - 1) + v17[1] + *v17 + v6[1] + *v6)
           + v17[1])
          + v20 * (v12[1] + *v12 + v19[1] + (unsigned int)*v19)
          + 0x8000) >> 16;
    v7 += 2;
  }
  return result;
}

