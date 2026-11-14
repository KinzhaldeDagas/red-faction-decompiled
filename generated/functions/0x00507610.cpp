// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507610 sub_507610
// UNREALRED VERIFIED [vclip-name-precedence]: Empty name returns -1. Scans 64 registry slots in ascending order, compares names with _stricmp, and returns immediately on first match; unmatched returns -1. Thus first case-insensitive duplicate wins, including retail glassboom (30 particles) before Glassboom (40). This must also select the first definition for Foley, damage and explosion fields; a last-write-wins normalized map is not equivalent. Invalid ID -1 yields zero in particle-count getter 0x507830, so unknown VClip names do not suppress authored clutter debris.
int __cdecl sub_507610(char *String2)
{
  const char *v2; // eax
  int i; // [esp+10h] [ebp-4h]

  if ( !strlen(String2) )
    return -1;
  for ( i = 0; i < 64; ++i )
  {
    v2 = rf_string_object_c_str_or_empty((char *)&unk_90DC80 + 224 * i);
    if ( !_stricmp(v2, String2) )
      return i;
  }
  return -1;
}

