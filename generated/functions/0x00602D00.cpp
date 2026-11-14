// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00602D00 rf_jpeg_prep_pre_process_data
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcprepct.c:pre_process_data matched): Seven-argument preprocessing callback. Converts input rows into the color buffer, updating input count, next_buf_row and rows_to_go. Each full max_v group is downsampled into the next output row group. At image end, repeats the final converted row to complete a group, then repeats the last output row per component to fill the requested output group capacity. Row counts are integers; the old pointer inference in the padding helper was incorrect.
unsigned int __cdecl rf_jpeg_prep_pre_process_data(
        _DWORD *a1,
        int a2,
        unsigned int *a3,
        unsigned int a4,
        int a5,
        unsigned int *a6,
        unsigned int a7)
{
  unsigned int result; // eax
  int v8; // [esp+0h] [ebp-18h]
  int v9; // [esp+8h] [ebp-10h]
  int i; // [esp+Ch] [ebp-Ch]
  int v11; // [esp+Ch] [ebp-Ch]
  int v12; // [esp+10h] [ebp-8h]

  v9 = a1[84];
  while ( 1 )
  {
    result = *a3;
    if ( *a3 >= a4 || *a6 >= a7 )
      break;
    if ( a1[58] - *(_DWORD *)(v9 + 52) >= a4 - *a3 )
      v8 = a4 - *a3;
    else
      v8 = a1[58] - *(_DWORD *)(v9 + 52);
    (*(void (__cdecl **)(_DWORD *, unsigned int, int, _DWORD, int))(a1[87] + 4))(
      a1,
      a2 + 4 * *a3,
      v9 + 8,
      *(_DWORD *)(v9 + 52),
      v8);
    *a3 += v8;
    *(_DWORD *)(v9 + 52) += v8;
    *(_DWORD *)(v9 + 48) -= v8;
    if ( !*(_DWORD *)(v9 + 48) && *(_DWORD *)(v9 + 52) < a1[58] )
    {
      for ( i = 0; i < a1[14]; ++i )
        rf_jpeg_prep_expand_bottom_edge(*(unsigned __int8 ***)(v9 + 4 * i + 8), a1[7], *(_DWORD *)(v9 + 52), a1[58]);
      *(_DWORD *)(v9 + 52) = a1[58];
    }
    if ( *(_DWORD *)(v9 + 52) == a1[58] )
    {
      (*(void (__cdecl **)(_DWORD *, int, _DWORD, int, _DWORD))(a1[88] + 4))(a1, v9 + 8, 0, a5, *a6);
      *(_DWORD *)(v9 + 52) = 0;
      ++*a6;
    }
    if ( !*(_DWORD *)(v9 + 48) && *a6 < a7 )
    {
      v11 = 0;
      v12 = a1[16];
      while ( v11 < a1[14] )
      {
        rf_jpeg_prep_expand_bottom_edge(
          *(unsigned __int8 ***)(a5 + 4 * v11++),
          8 * *(_DWORD *)(v12 + 28),
          *(_DWORD *)(v12 + 12) * *a6,
          *(_DWORD *)(v12 + 12) * a7);
        v12 += 84;
      }
      *a6 = a7;
      return a7;
    }
  }
  return result;
}

