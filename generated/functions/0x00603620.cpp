// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00603620 rf_jpeg_downsample_integer_box
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcsample.c:int_downsample matched): Generic integer box downsampling. hExpand=max_h/h_samp, vExpand=max_v/v_samp, outputWidth=8*width_in_blocks. Pads the INPUT right edge to hExpand*outputWidth. Each output sample is (sum + area/2)/area over hExpand*vExpand pixels. Initializer guarantees positive integral sampling ratios.
_BYTE *__cdecl rf_jpeg_downsample_integer_box(_DWORD *a1, _DWORD *a2, int a3, int a4)
{
  _BYTE *result; // eax
  int v5; // [esp+0h] [ebp-38h]
  unsigned int v6; // [esp+8h] [ebp-30h]
  _BYTE *v7; // [esp+Ch] [ebp-2Ch]
  int v8; // [esp+10h] [ebp-28h]
  unsigned int v9; // [esp+14h] [ebp-24h]
  int i; // [esp+18h] [ebp-20h]
  unsigned __int8 *v11; // [esp+1Ch] [ebp-1Ch]
  int v12; // [esp+20h] [ebp-18h]
  int v13; // [esp+24h] [ebp-14h]
  int k; // [esp+28h] [ebp-10h]
  int j; // [esp+2Ch] [ebp-Ch]
  int v16; // [esp+30h] [ebp-8h]

  v9 = 8 * a2[7];
  v8 = a1[57] / a2[2];
  v12 = a1[58] / a2[3];
  result = rf_jpeg_downsample_expand_right_edge(a3, a1[58], a1[7], v8 * v9);
  v5 = 0;
  for ( i = 0; i < a2[3]; ++i )
  {
    v7 = *(_BYTE **)(a4 + 4 * i);
    v6 = 0;
    v13 = 0;
    while ( v6 < v9 )
    {
      v16 = 0;
      for ( j = 0; j < v12; ++j )
      {
        v11 = (unsigned __int8 *)(v13 + *(_DWORD *)(a3 + 4 * (j + v5)));
        for ( k = 0; k < v8; ++k )
          v16 += *v11++;
      }
      *v7++ = (v12 * v8 / 2 + v16) / (v12 * v8);
      ++v6;
      v13 += v8;
    }
    v5 += v12;
    result = (_BYTE *)(i + 1);
  }
  return result;
}

