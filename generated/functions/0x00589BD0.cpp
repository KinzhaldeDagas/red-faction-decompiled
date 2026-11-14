// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589BD0 rf_character_cache_contains_loaded_filename
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Copies input unbounded into32-byte local name buffer, removes suffix at last dot (without directory awareness), then scans64 slots for loaded bit1 plus case-insensitive exact name. Returns1 on match,0 otherwise. Does not load or pin; overly long input can exceed the local buffer.
int __cdecl rf_character_cache_contains_loaded_filename(char *a1)
{
  char v1; // al
  char *v3; // [esp+8h] [ebp-34h]
  char String2[32]; // [esp+10h] [ebp-2Ch] BYREF
  char *last_char_wrapper; // [esp+34h] [ebp-8h]
  int i; // [esp+38h] [ebp-4h]

  v3 = String2;
  do
  {
    v1 = *a1;
    *v3++ = *a1++;
  }
  while ( v1 );
  last_char_wrapper = rf_cstring_find_last_char_wrapper(String2, 46);
  if ( last_char_wrapper )
    *last_char_wrapper = 0;
  for ( i = 0; i < 64; ++i )
  {
    if ( (dword_18D0A74[1686 * i] & 1) != 0 && !_stricmp(&byte_18D0A30[6744 * i], String2) )
      return 1;
  }
  return 0;
}

