// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B720 rf_settings_toggle_autoswitch_weapons
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Full native callback contract:normalize logical-not checkboxBYTE6F8098 (any nonzero->0,zero->1),copy direct boolean into unchecked
// playerBYTE3904(F40). Newcheckbox true sound44,false45. No player/runtime/input guard,priority reorder,default mutation or configuration save. Stored int return sound residue;raw
// saved BYTE can initially be noncanonical but toggle normalizes it.
int rf_settings_toggle_autoswitch_weapons()
{
  byte_6F8098[0] = byte_6F8098[0] == 0;
  *(_BYTE *)(rf_local_fpgun_player + 3904) = byte_6F8098[0];
  if ( byte_6F8098[0] )
    return rf_gamesound_play_event(44, 0, 0.0, 1.0);
  else
    return rf_gamesound_play_event(45, 0, 0.0, 1.0);
}

