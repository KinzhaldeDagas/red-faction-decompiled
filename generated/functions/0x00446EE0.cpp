// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446EE0 rf_foley_definition_find_name
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Foley name lookup returns-1 for empty input; otherwise first case-insensitive exact name match across source-order44-byte rows. A normalized name map or merged duplicate-name variant array is not equivalent.
int __cdecl rf_foley_definition_find_name(char *String2)
{
  int i; // [esp+10h] [ebp-4h]

  if ( !strlen(String2) )
    return -1;
  for ( i = 0; i < unk_6EDC30; ++i )
  {
    if ( !_stricmp((const char *)&unk_6E6E30 + 44 * i, String2) )
      return i;
  }
  return -1;
}

