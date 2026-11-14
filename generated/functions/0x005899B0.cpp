// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005899B0 rf_character_cache_get_or_load
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Finds name across all slots; if absent calls allocate/load589A40. Failure produces fatal character.cpp:1554 message referring to charanim.tbl. Pin byte exactly1 sets flags+68 bit2 on returned record. Other values do not clear an existing pin. Does not independently validate loaded flag of a name match.
char *__cdecl rf_character_cache_get_or_load(char *String1, char a2)
{
  char *name_case_insensitive; // [esp+0h] [ebp-4h]

  name_case_insensitive = rf_character_cache_find_name_case_insensitive(String1);
  if ( !name_case_insensitive )
  {
    name_case_insensitive = rf_character_cache_allocate_and_load(String1);
    if ( !name_case_insensitive )
    {
      sprintf(&unk_18CD828, "Couldn't load character %s in charanim.tbl file.", String1);
      rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\ca\\character.cpp", 1554, &unk_18CD828);
    }
  }
  if ( a2 == 1 )
    *((_DWORD *)name_case_insensitive + 17) |= 2u;
  return name_case_insensitive;
}

