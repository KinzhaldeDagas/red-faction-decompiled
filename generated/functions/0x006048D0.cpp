// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006048D0 rf_jpeg_color_grayscale_convert
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccolor.c:grayscale_convert matched): Copies the first input byte of each pixel into gray plane 0, advancing by input_components. Thus gray input is copied and interleaved YCbCr input has its Y channel extracted. No lookup tables or averaging.
_BYTE *__cdecl rf_jpeg_color_grayscale_convert(int a1, _BYTE **a2, _DWORD *a3, int a4, int a5)
{
  _BYTE *result; // eax
  int v6; // [esp+0h] [ebp-14h]
  _BYTE *v7; // [esp+4h] [ebp-10h]
  _BYTE *v8; // [esp+8h] [ebp-Ch]
  unsigned int v9; // [esp+Ch] [ebp-8h]
  unsigned int i; // [esp+10h] [ebp-4h]

  v9 = *(_DWORD *)(a1 + 28);
  result = *(_BYTE **)(a1 + 36);
  v8 = result;
  while ( --a5 >= 0 )
  {
    v7 = *a2++;
    v6 = *(_DWORD *)(*a3 + 4 * a4);
    result = (_BYTE *)++a4;
    for ( i = 0; i < v9; ++i )
    {
      *(_BYTE *)(i + v6) = *v7;
      result = &v7[(_DWORD)v8];
      v7 = &v7[(_DWORD)v8];
    }
  }
  return result;
}

