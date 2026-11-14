// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC680 rf_object_find_by_saved_identifier
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Cdecl signed stable/saved identifier, compares common DWORD32 in global active list head7D0C90/sentinel7D0C80 using NEXT+16, distinct from typed-list links652. Input-1 returns0 without scan. Input-999 returns FIRST matching ID only when common flags124 mask2 is clear; all other IDs return first equality regardless of deletion flags/type. No generation-handle validation, allocation, mutation or null/list guard; not equivalent to runtime handle resolver40CE70.
int __cdecl rf_object_find_by_saved_identifier(int a1)
{
  int j; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  if ( a1 == -1 )
    return 0;
  if ( a1 == -999 )
  {
    for ( i = unk_7D0C90; (_UNKNOWN *)i != &unk_7D0C80; i = *(_DWORD *)(i + 16) )
    {
      if ( *(_DWORD *)(i + 32) == -999 && (*(_DWORD *)(i + 124) & 2) == 0 )
        return i;
    }
  }
  else
  {
    for ( j = unk_7D0C90; (_UNKNOWN *)j != &unk_7D0C80; j = *(_DWORD *)(j + 16) )
    {
      if ( *(_DWORD *)(j + 32) == a1 )
        return j;
    }
  }
  return 0;
}

