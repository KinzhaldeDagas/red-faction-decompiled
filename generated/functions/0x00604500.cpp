// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00604500 rf_jpeg_color_rgb_ycc_convert
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccolor.c:rgb_ycc_convert matched): Five-argument color callback (cinfo, inputRows, outputPlanes, outputRow, numRows). Converts interleaved RGB bytes to separate Y/Cb/Cr planes using the fixed-point tables, shifting summed entries by 16. Processes image_width samples per row. Input order is R,G,B; there is no alpha or gamma conversion.
int __cdecl rf_jpeg_color_rgb_ycc_convert(int a1, unsigned __int8 **a2, _DWORD *a3, int a4, int a5)
{
  int result; // eax
  int v6; // [esp+0h] [ebp-2Ch]
  int v7; // [esp+4h] [ebp-28h]
  int v8; // [esp+8h] [ebp-24h]
  int v9; // [esp+Ch] [ebp-20h]
  int v10; // [esp+10h] [ebp-1Ch]
  int v11; // [esp+18h] [ebp-14h]
  unsigned __int8 *v12; // [esp+1Ch] [ebp-10h]
  int v13; // [esp+20h] [ebp-Ch]
  unsigned int v14; // [esp+24h] [ebp-8h]
  unsigned int i; // [esp+28h] [ebp-4h]

  v11 = *(_DWORD *)(*(_DWORD *)(a1 + 348) + 8);
  v14 = *(_DWORD *)(a1 + 28);
  while ( 1 )
  {
    result = --a5;
    if ( a5 < 0 )
      break;
    v12 = *a2++;
    v6 = *(_DWORD *)(*a3 + 4 * a4);
    v7 = *(_DWORD *)(a3[1] + 4 * a4);
    v13 = *(_DWORD *)(a3[2] + 4 * a4++);
    for ( i = 0; i < v14; ++i )
    {
      v8 = *v12;
      v9 = v12[1];
      v10 = v12[2];
      v12 += 3;
      *(_BYTE *)(i + v6) = (unsigned int)(*(_DWORD *)(v11 + 4 * v10 + 2048)
                                        + *(_DWORD *)(v11 + 4 * v9 + 1024)
                                        + *(_DWORD *)(v11 + 4 * v8)) >> 16;
      *(_BYTE *)(i + v7) = (unsigned int)(*(_DWORD *)(v11 + 4 * v10 + 5120)
                                        + *(_DWORD *)(v11 + 4 * v9 + 4096)
                                        + *(_DWORD *)(v11 + 4 * v8 + 3072)) >> 16;
      *(_BYTE *)(i + v13) = (unsigned int)(*(_DWORD *)(v11 + 4 * v10 + 7168)
                                         + *(_DWORD *)(v11 + 4 * v9 + 6144)
                                         + *(_DWORD *)(v11 + 4 * v8 + 5120)) >> 16;
    }
  }
  return result;
}

