// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DE9E0 rf_multiplayer_character_needs_default_team_skins
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): Cdecl multiplayer-character record,entity-class definition. If inline character skin name+48 is not case-insensitive default, false. If signed class profile count3964<2, true; otherwise tests ONLY last profile name RFString3968+108*(count-1), true unless case-insensitive default_blue. Does not check previous default_red, pair validity, material counts, file existence or count upper bound. No own pointers/record-index validation.
bool __cdecl rf_multiplayer_character_needs_default_team_skins(int a1, int a2)
{
  const char *v3; // eax

  if ( _stricmp((const char *)(a1 + 48), "default") )
    return 0;
  if ( *(int *)(a2 + 3964) < 2 )
    return 1;
  v3 = rf_string_object_c_str_or_empty((const void *)(a2 + 108 * (*(_DWORD *)(a2 + 3964) - 1) + 3968));
  return _stricmp(v3, "default_blue") != 0;
}

