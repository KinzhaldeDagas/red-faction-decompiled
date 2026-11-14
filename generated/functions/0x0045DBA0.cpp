// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DBA0 rf_multiplayer_game_mode_index_from_name
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl candidateCstring. Case-insensitive FULL strcmp against original three names661E9C:DM->0,CTF->1,TeamDM->2;first
// exact match returns index,otherwise-1. No prefix/suffix tolerance,whitespace trim,localized label lookup,NULL guard or mode-state mutation. Distinct from level-prefix
// predicate45B4D0 (dm/ctf/dm);TeamDM is not a unique filename prefix.
int __cdecl rf_multiplayer_game_mode_index_from_name(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 3; ++i )
  {
    if ( !_stricmp((&off_661E9C)[i], String2) )
      return i;
  }
  return -1;
}

