// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00431680 sub_431680
// UNREALRED VERIFIED [lan-killfeed-20261028] Resolves an entities.tbl entity-definition name case-insensitively over the loaded definition count and returns its zero-based index, or -1. Pronoun helper0x49BBF0 uses this on literal multi_female, compared to selected pc_multi $EntityAnimType: index.
int __cdecl sub_431680(char *String1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_681E14; ++i )
  {
    if ( rf_cstring_equals_rf_string_case_insensitive(String1, (int)&rf_entity_info_definitions[5396 * i]) )
      return i;
  }
  return -1;
}

