// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00603790 rf_jpeg_downsample_expand_right_edge
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcsample.c:expand_right_edge matched): For each of numRows, repeats the byte at inputCols-1 into columns inputCols..outputCols-1. Nonpositive extension does nothing. Does not validate inputCols > 0 or destination capacity. Callers may use it on input or output rows.
_BYTE *__cdecl rf_jpeg_downsample_expand_right_edge(int a1, int a2, int a3, int a4)
{
  _BYTE *result; // eax
  int i; // [esp+0h] [ebp-14h]
  _BYTE *v6; // [esp+4h] [ebp-10h]
  char v7; // [esp+Bh] [ebp-9h]
  int j; // [esp+Ch] [ebp-8h]

  result = (_BYTE *)(a4 - a3);
  if ( a4 - a3 > 0 )
  {
    for ( i = 0; i < a2; ++i )
    {
      v6 = (_BYTE *)(a3 + *(_DWORD *)(a1 + 4 * i));
      result = v6;
      v7 = *(v6 - 1);
      for ( j = a4 - a3; j > 0; --j )
      {
        *v6++ = v7;
        result = (_BYTE *)(j - 1);
      }
    }
  }
  return result;
}

