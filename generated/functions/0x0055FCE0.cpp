// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055FCE0 rf_string_trim_leading_space_tab_lf
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Object in ECX, no stack args (old fastcall label describes the same register input). If buffer exists, scans current strlen prefix for only space32,tab9,LF10; CR is retained. If prefix count equals STORED extent, frees/clears buffer but keeps extent. Else a positive prefix is shifted out by a forward byte copy including NUL. Never updates extent, reallocates, or normalizes capacity. Return EAX is incidental, varying among index/byte/pointer.
int __fastcall rf_string_trim_leading_space_tab_lf(int a1)
{
  int result; // eax
  char v2; // dl
  char *v3; // [esp+8h] [ebp-24h]
  char *v4; // [esp+Ch] [ebp-20h]
  signed int v5; // [esp+24h] [ebp-8h]
  int i; // [esp+28h] [ebp-4h]

  result = a1;
  if ( *(_DWORD *)(a1 + 4) )
  {
    v5 = strlen(*(const char **)(a1 + 4));
    for ( i = 0; ; ++i )
    {
      result = i;
      if ( i >= v5 )
        break;
      if ( *(_BYTE *)(*(_DWORD *)(a1 + 4) + i) != 32 && *(_BYTE *)(*(_DWORD *)(a1 + 4) + i) != 9 )
      {
        result = *(char *)(*(_DWORD *)(a1 + 4) + i);
        if ( result != 10 )
          break;
      }
    }
    if ( i == *(_DWORD *)a1 )
    {
      return (int)rf_string_release_buffer_keep_extent((_DWORD *)a1);
    }
    else if ( i > 0 )
    {
      v4 = (char *)(i + *(_DWORD *)(a1 + 4));
      v3 = *(char **)(a1 + 4);
      do
      {
        v2 = *v4;
        *v3 = *v4;
        result = (int)++v4;
        ++v3;
      }
      while ( v2 );
    }
  }
  return result;
}

