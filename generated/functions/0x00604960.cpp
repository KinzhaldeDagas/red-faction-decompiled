// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00604960 rf_jpeg_color_null_convert
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccolor.c:null_convert matched): Deinterleaves matching input components into separate output planes. For each row and component i, copies input byte i from each pixel, stepping by num_components. Despite the source name null_convert, this performs the planar layout conversion.
unsigned int __cdecl rf_jpeg_color_null_convert(int a1, int *a2, int a3, int a4, int a5)
{
  unsigned int result; // eax
  int v6; // [esp+0h] [ebp-18h]
  int v7; // [esp+4h] [ebp-14h]
  int v8; // [esp+8h] [ebp-10h]
  int i; // [esp+Ch] [ebp-Ch]
  unsigned int v10; // [esp+10h] [ebp-8h]
  unsigned int j; // [esp+14h] [ebp-4h]

  v7 = *(_DWORD *)(a1 + 56);
  result = *(_DWORD *)(a1 + 28);
  v10 = result;
  while ( --a5 >= 0 )
  {
    for ( i = 0; i < v7; ++i )
    {
      v8 = *a2;
      v6 = *(_DWORD *)(*(_DWORD *)(a3 + 4 * i) + 4 * a4);
      for ( j = 0; j < v10; ++j )
      {
        *(_BYTE *)(j + v6) = *(_BYTE *)(i + v8);
        v8 += v7;
      }
    }
    ++a2;
    result = ++a4;
  }
  return result;
}

