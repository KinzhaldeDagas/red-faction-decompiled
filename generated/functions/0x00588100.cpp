// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00588100 rf_character_record_release_resources
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Releases each loaded148-byte descriptor for count+6588. For handle list+3932,count+3928, skips an occurrence when same handle appears later in this record, so processes each unique handle once. Searches all OTHER loaded cache records and their handle lists; passes release flag1 to5BA3A0 only if handle is unshared, otherwise0. Clears handle count/name then resets header, including all cache flags. Does not delete containing slot. Assumes counts/pointers valid.
int __cdecl rf_character_record_release_resources(int a1)
{
  char *v2; // [esp+4h] [ebp-18h]
  int k; // [esp+8h] [ebp-14h]
  char v4; // [esp+Fh] [ebp-Dh]
  int m; // [esp+10h] [ebp-Ch]
  int n; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]
  int j; // [esp+18h] [ebp-4h]
  unsigned __int8 v9; // [esp+28h] [ebp+Ch]

  for ( i = 0; i < *(_DWORD *)(a1 + 6588); ++i )
    rf_v3c_asset148_release_arrays((void *)(a1 + 148 * i + 6592));
  for ( j = 0; j < *(_DWORD *)(a1 + 3928); ++j )
  {
    v9 = 1;
    v4 = 0;
    for ( k = j + 1; k < *(_DWORD *)(a1 + 3928); ++k )
    {
      if ( *(_DWORD *)(a1 + 4 * j + 3932) == *(_DWORD *)(a1 + 4 * k + 3932) )
      {
        v4 = 1;
        break;
      }
    }
    if ( v4 != 1 )
    {
      for ( m = 0; m < 64 && v9 == 1; ++m )
      {
        v2 = &byte_18D0A30[6744 * m];
        if ( (*((_DWORD *)v2 + 17) & 1) != 0 && v2 != (char *)a1 )
        {
          for ( n = 0; n < *((_DWORD *)v2 + 982); ++n )
          {
            if ( *(_DWORD *)&v2[4 * n + 3932] == *(_DWORD *)(a1 + 4 * j + 3932) )
            {
              v9 = 0;
              break;
            }
          }
        }
      }
      rf_animation_clip_release_if_requested(*(_DWORD *)(a1 + 4 * j + 3932), v9);
    }
  }
  *(_DWORD *)(a1 + 3928) = 0;
  *(_BYTE *)a1 = 0;
  return rf_character_record_reset_header(a1);
}

