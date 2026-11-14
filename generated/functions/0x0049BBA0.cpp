// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049BBA0 rf_multiplayer_character_find_by_name
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet registry, field permutations, x87 transfers, face-list mutation and HUD native stores): Cdecl
// input C-string, signed index result. For index=0 while index < signed DWORD character count77FE20, compare name at77D76C+320*index to input using case-insensitive CRT _stricmp.
// Return FIRST equal index, otherwise -1. Nonpositive count returns -1 without dereferencing input. No NULL-string, record-capacity or string-length guard; no fallback character
// selection inside this helper. Existing respawn selection note is confirmed by full native body.
int __cdecl rf_multiplayer_character_find_by_name(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_multiplayer_character_count; ++i )
  {
    if ( !_stricmp((const char *)&unk_77D76C + 320 * i, String2) )
      return i;
  }
  return -1;
}

