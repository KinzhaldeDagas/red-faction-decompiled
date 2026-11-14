// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589950 rf_character_cache_find_name_case_insensitive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Scans all64 slot names with _stricmp and returns first record pointer, elseNULL. Does NOT require loaded bit1, so empty names and names retained after failed loading can match inactive slots. No basename/extension normalization here.
char *__cdecl rf_character_cache_find_name_case_insensitive(char *String1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 64; ++i )
  {
    if ( !_stricmp(String1, &byte_18D0A30[6744 * i]) )
      return &byte_18D0A30[6744 * i];
  }
  return nullptr;
}

