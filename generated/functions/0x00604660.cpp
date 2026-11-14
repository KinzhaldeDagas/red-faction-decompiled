// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00604660 rf_jpeg_color_rgb_gray_convert
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccolor.c:rgb_gray_convert matched): Converts interleaved RGB rows to gray plane 0 using (19595*R+38470*G+7471*B+32768)>>16 through the lookup tables. Processes image_width pixels for each supplied row. Start-pass must initialize the tables.
int __cdecl rf_jpeg_color_rgb_gray_convert(int a1, unsigned __int8 **a2, _DWORD *a3, int a4, int a5)
{
  int result; // eax
  int v6; // [esp+0h] [ebp-24h]
  int v7; // [esp+4h] [ebp-20h]
  int v8; // [esp+8h] [ebp-1Ch]
  int v9; // [esp+Ch] [ebp-18h]
  int v10; // [esp+14h] [ebp-10h]
  unsigned __int8 *v11; // [esp+18h] [ebp-Ch]
  unsigned int v12; // [esp+1Ch] [ebp-8h]
  unsigned int i; // [esp+20h] [ebp-4h]

  v10 = *(_DWORD *)(*(_DWORD *)(a1 + 348) + 8);
  v12 = *(_DWORD *)(a1 + 28);
  while ( 1 )
  {
    result = --a5;
    if ( a5 < 0 )
      break;
    v11 = *a2++;
    v7 = *(_DWORD *)(*a3 + 4 * a4++);
    for ( i = 0; i < v12; ++i )
    {
      v6 = *v11;
      v8 = v11[1];
      v9 = v11[2];
      v11 += 3;
      *(_BYTE *)(i + v7) = (unsigned int)(*(_DWORD *)(v10 + 4 * v9 + 2048)
                                        + *(_DWORD *)(v10 + 4 * v8 + 1024)
                                        + *(_DWORD *)(v10 + 4 * v6)) >> 16;
    }
  }
  return result;
}

