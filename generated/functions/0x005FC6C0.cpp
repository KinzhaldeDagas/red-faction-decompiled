// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FC6C0 rf_jpeg_suppress_tables
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcapimin.c:jpeg_suppress_tables matched): Cdecl(cinfo,suppress int). For each4quant table pointers68+,ifnonNULL,stores suppress into sent_table128;for4DC and4AC Huffman pointers84+/100+,stores sent_table276. No Boolean normalization,state check or data output. Changes whether subsequent stream headers emit defined tables;voidAPI,incidental EAX4.
int __cdecl rf_jpeg_suppress_tables(int a1, int a2)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-Ch]
  int v4; // [esp+0h] [ebp-Ch]
  int v5; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]
  int j; // [esp+8h] [ebp-4h]

  for ( i = 0; i < 4; ++i )
  {
    v5 = *(_DWORD *)(a1 + 4 * i + 68);
    if ( v5 )
      *(_DWORD *)(v5 + 128) = a2;
    result = i + 1;
  }
  for ( j = 0; j < 4; ++j )
  {
    v3 = *(_DWORD *)(a1 + 4 * j + 84);
    if ( v3 )
      *(_DWORD *)(v3 + 276) = a2;
    v4 = *(_DWORD *)(a1 + 4 * j + 100);
    if ( v4 )
      *(_DWORD *)(v4 + 276) = a2;
    result = j + 1;
  }
  return result;
}

