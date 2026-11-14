// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00603940 rf_jpeg_downsample_h2v2
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcsample.c:h2v2_downsample matched): Horizontal and vertical 2:1 downsampling. Pads INPUT rows to twice the output width; each output is the average of a 2x2 block using (sum+bias)>>2. Bias alternates 1/2 across columns and resets to one each output row.
int __cdecl rf_jpeg_downsample_h2v2(int a1, int a2, int a3, int a4)
{
  int result; // eax
  int v5; // [esp+0h] [ebp-20h]
  unsigned int j; // [esp+4h] [ebp-1Ch]
  _BYTE *v7; // [esp+8h] [ebp-18h]
  unsigned __int8 *v8; // [esp+Ch] [ebp-14h]
  unsigned int v9; // [esp+10h] [ebp-10h]
  int i; // [esp+14h] [ebp-Ch]
  int v11; // [esp+18h] [ebp-8h]
  unsigned __int8 *v12; // [esp+1Ch] [ebp-4h]

  v9 = 8 * *(_DWORD *)(a2 + 28);
  rf_jpeg_downsample_expand_right_edge(a3, *(_DWORD *)(a1 + 232), *(_DWORD *)(a1 + 28), 16 * *(_DWORD *)(a2 + 28));
  v5 = 0;
  for ( i = 0; ; ++i )
  {
    result = a2;
    if ( i >= *(_DWORD *)(a2 + 12) )
      break;
    v7 = *(_BYTE **)(a4 + 4 * i);
    v12 = *(unsigned __int8 **)(a3 + 4 * v5);
    v8 = *(unsigned __int8 **)(a3 + 4 * v5 + 4);
    v11 = 1;
    for ( j = 0; j < v9; ++j )
    {
      *v7++ = (v11 + *v8 + v12[1] + *v12 + v8[1]) >> 2;
      v11 ^= 3u;
      v12 += 2;
      v8 += 2;
    }
    v5 += 2;
  }
  return result;
}

