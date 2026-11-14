// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00604740 rf_jpeg_color_cmyk_ycck_convert
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccolor.c:cmyk_ycck_convert matched): Converts interleaved CMYK to planar YCCK. Forms R=255-C, G=255-M, B=255-Y, applies the RGB-to-YCbCr tables, and copies K unchanged to plane 3. No K inversion or ICC conversion.
int __cdecl rf_jpeg_color_cmyk_ycck_convert(int a1, unsigned __int8 **a2, _DWORD *a3, int a4, int a5)
{
  int result; // eax
  int v6; // [esp+0h] [ebp-30h]
  int v7; // [esp+4h] [ebp-2Ch]
  int v8; // [esp+8h] [ebp-28h]
  int v9; // [esp+Ch] [ebp-24h]
  int v10; // [esp+10h] [ebp-20h]
  int v11; // [esp+14h] [ebp-1Ch]
  int v12; // [esp+1Ch] [ebp-14h]
  unsigned __int8 *v13; // [esp+20h] [ebp-10h]
  int v14; // [esp+24h] [ebp-Ch]
  unsigned int v15; // [esp+28h] [ebp-8h]
  unsigned int i; // [esp+2Ch] [ebp-4h]

  v12 = *(_DWORD *)(*(_DWORD *)(a1 + 348) + 8);
  v15 = *(_DWORD *)(a1 + 28);
  while ( 1 )
  {
    result = --a5;
    if ( a5 < 0 )
      break;
    v13 = *a2++;
    v6 = *(_DWORD *)(*a3 + 4 * a4);
    v7 = *(_DWORD *)(a3[1] + 4 * a4);
    v14 = *(_DWORD *)(a3[2] + 4 * a4);
    v8 = *(_DWORD *)(a3[3] + 4 * a4++);
    for ( i = 0; i < v15; ++i )
    {
      v9 = 255 - *v13;
      v10 = 255 - v13[1];
      v11 = 255 - v13[2];
      *(_BYTE *)(i + v8) = v13[3];
      v13 += 4;
      *(_BYTE *)(i + v6) = (unsigned int)(*(_DWORD *)(v12 + 4 * v11 + 2048)
                                        + *(_DWORD *)(v12 + 4 * v10 + 1024)
                                        + *(_DWORD *)(v12 + 4 * v9)) >> 16;
      *(_BYTE *)(i + v7) = (unsigned int)(*(_DWORD *)(v12 + 4 * v11 + 5120)
                                        + *(_DWORD *)(v12 + 4 * v10 + 4096)
                                        + *(_DWORD *)(v12 + 4 * v9 + 3072)) >> 16;
      *(_BYTE *)(i + v14) = (unsigned int)(*(_DWORD *)(v12 + 4 * v11 + 7168)
                                         + *(_DWORD *)(v12 + 4 * v10 + 6144)
                                         + *(_DWORD *)(v12 + 4 * v9 + 5120)) >> 16;
    }
  }
  return result;
}

