// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00420F80 rf_entity_info_find_animation_record_by_name
// VERIFIED: Resolves a case-insensitive authored animation descriptor against character-definition animation records and returns the matching record index or -1. sub_42CB80 calls it for each of 45 descriptor slots.
// UNREALRED VERIFIED [general-gap-20260830]: Case-insensitively resolves an authored animation descriptor against the character-definition animation records and returns its record index or -1.
int __cdecl rf_entity_info_find_animation_record_by_name(_DWORD *a1, int a2, int a3, int a4, char a5)
{
  char *v6; // [esp+0h] [ebp-8h]
  int k; // [esp+4h] [ebp-4h]
  int m; // [esp+4h] [ebp-4h]
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]

  v6 = &rf_entity_info_definitions[5396 * a2];
  if ( a3 < 0 )
  {
    if ( a5 == 1 )
    {
      for ( i = 0; i < *((_DWORD *)v6 + 469); ++i )
      {
        if ( rf_string_object_equals_case_insensitive(a4, *((_DWORD *)v6 + 471) + 52 * i) )
        {
          rf_string_assign_from_object(a1, *((_DWORD *)v6 + 471) + 52 * i + 8);
          return i;
        }
      }
    }
    else
    {
      for ( j = 0; j < *((_DWORD *)v6 + 470); ++j )
      {
        if ( rf_string_object_equals_case_insensitive(a4, *((_DWORD *)v6 + 472) + 52 * j) )
        {
          rf_string_assign_from_object(a1, *((_DWORD *)v6 + 472) + 52 * j + 8);
          return j;
        }
      }
    }
    return -1;
  }
  else
  {
    if ( a5 == 1 )
    {
      for ( k = 0; k < *(_DWORD *)&v6[4 * a3 + 1896]; ++k )
      {
        if ( rf_string_object_equals_case_insensitive(a4, *(_DWORD *)&v6[4 * a3 + 2408] + 52 * k) )
        {
          rf_string_assign_from_object(a1, *(_DWORD *)&v6[4 * a3 + 2408] + 52 * k + 8);
          return k;
        }
      }
    }
    else
    {
      for ( m = 0; m < *(_DWORD *)&v6[4 * a3 + 2152]; ++m )
      {
        if ( rf_string_object_equals_case_insensitive(a4, *(_DWORD *)&v6[4 * a3 + 2664] + 52 * m) )
        {
          rf_string_assign_from_object(a1, *(_DWORD *)&v6[4 * a3 + 2664] + 52 * m + 8);
          return m;
        }
      }
    }
    return -1;
  }
}

