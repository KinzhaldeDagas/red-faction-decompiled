// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00602F70 rf_jpeg_prep_pre_process_context
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcprepct.c:pre_process_context matched): Context preprocessing callback using a ring of 3*max_v actual rows plus aliased pointer margins. Initially fills two groups, replicating the first row into negative context indices. At image end, repeats the last row to the next stop. Downsamples this_row_group when ready, advances by max_v and wraps at 3*max_v. If input ends before the image is complete, returns to await more input. Provides the neighboring rows required by smoothing.
size_t __cdecl rf_jpeg_prep_pre_process_context(
        size_t *a1,
        int a2,
        unsigned int *a3,
        unsigned int a4,
        int a5,
        unsigned int *a6,
        unsigned int a7)
{
  size_t result; // eax
  int v8; // [esp+0h] [ebp-1Ch]
  signed int k; // [esp+4h] [ebp-18h]
  _DWORD *v10; // [esp+Ch] [ebp-10h]
  signed int j; // [esp+10h] [ebp-Ch]
  signed int i; // [esp+10h] [ebp-Ch]
  signed int v13; // [esp+14h] [ebp-8h]

  v10 = (_DWORD *)a1[84];
  result = 3 * a1[58];
  v13 = result;
  while ( *a6 < a7 )
  {
    result = (size_t)a3;
    if ( *a3 >= a4 )
    {
      if ( v10[12] )
        return result;
      if ( v10[13] < v10[15] )
      {
        for ( i = 0; i < (int)a1[14]; ++i )
          rf_jpeg_prep_expand_bottom_edge((unsigned __int8 **)v10[i + 2], a1[7], v10[13], v10[15]);
        v10[13] = v10[15];
      }
    }
    else
    {
      if ( v10[15] - v10[13] >= a4 - *a3 )
        v8 = a4 - *a3;
      else
        v8 = v10[15] - v10[13];
      (*(void (__cdecl **)(size_t *, unsigned int, _DWORD *, _DWORD, int))(a1[87] + 4))(
        a1,
        a2 + 4 * *a3,
        v10 + 2,
        v10[13],
        v8);
      if ( v10[12] == a1[8] )
      {
        for ( j = 0; j < (int)a1[14]; ++j )
        {
          for ( k = 1; k <= (int)a1[58]; ++k )
            rf_jpeg_jcopy_sample_rows(v10[j + 2], 0, v10[j + 2], -k, 1, a1[7]);
        }
      }
      *a3 += v8;
      v10[13] += v8;
      v10[12] -= v8;
    }
    result = (size_t)v10;
    if ( v10[13] == v10[15] )
    {
      (*(void (__cdecl **)(size_t *, _DWORD *, _DWORD, int, _DWORD))(a1[88] + 4))(a1, v10 + 2, v10[14], a5, *a6);
      ++*a6;
      v10[14] += a1[58];
      if ( v10[14] >= v13 )
        v10[14] = 0;
      if ( v10[13] >= v13 )
        v10[13] = 0;
      result = a1[58] + v10[13];
      v10[15] = result;
    }
  }
  return result;
}

