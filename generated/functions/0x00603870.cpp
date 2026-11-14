// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00603870 rf_jpeg_downsample_h2v1
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcsample.c:h2v1_downsample matched): Horizontal 2:1 downsampling. Pads INPUT rows to twice the output width, then computes (a+b+bias)>>1 for each pixel pair. Bias alternates 0/1 across columns and resets to zero each row. No vertical averaging or smoothing.
int __cdecl rf_jpeg_downsample_h2v1(int a1, int a2, int a3, int a4)
{
  int result; // eax
  unsigned int j; // [esp+0h] [ebp-18h]
  _BYTE *v6; // [esp+4h] [ebp-14h]
  unsigned int v7; // [esp+8h] [ebp-10h]
  int i; // [esp+Ch] [ebp-Ch]
  unsigned __int8 *v9; // [esp+10h] [ebp-8h]
  int v10; // [esp+14h] [ebp-4h]

  v7 = 8 * *(_DWORD *)(a2 + 28);
  rf_jpeg_downsample_expand_right_edge(a3, *(_DWORD *)(a1 + 232), *(_DWORD *)(a1 + 28), 16 * *(_DWORD *)(a2 + 28));
  for ( i = 0; ; ++i )
  {
    result = a2;
    if ( i >= *(_DWORD *)(a2 + 12) )
      break;
    v6 = *(_BYTE **)(a4 + 4 * i);
    v9 = *(unsigned __int8 **)(a3 + 4 * i);
    v10 = 0;
    for ( j = 0; j < v7; ++j )
    {
      *v6++ = (v10 + *v9 + v9[1]) >> 1;
      v10 ^= 1u;
      v9 += 2;
    }
  }
  return result;
}

