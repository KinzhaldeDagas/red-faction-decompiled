// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BB430 rf_object_has_player_flag
// UNREALRED VERIFIED [mission-startup-20261020] Direct player-flag predicate: non-null common object and common flags+0x7C bit8. Trigger NPC policy0 uses this; it is narrower than0x4BCF40 player-association lookup.
bool __cdecl rf_object_has_player_flag(int a1)
{
  return a1 && (*(_DWORD *)(a1 + 124) & 8) != 0;
}

