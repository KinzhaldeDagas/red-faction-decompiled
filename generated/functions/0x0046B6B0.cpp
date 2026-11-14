// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B6B0 rf_settings_toggle_first_person_weapon
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Noarg. Normalize logical-not checkboxBYTE6F7D08(any nonzero->0,zero->1),copy unchecked localPlayerBYTE3894(F36). Newtrue sound44,newfalse45. Original
// gameplay builder Show 1st Person Weapon fallback,callback6F7CE0 and player field load independently verified. No runtime/player/input admission,default mutation or file
// save;immediate player preference write.
int rf_settings_toggle_first_person_weapon()
{
  byte_6F7D08[0] = byte_6F7D08[0] == 0;
  *(_BYTE *)(rf_local_fpgun_player + 3894) = byte_6F7D08[0];
  if ( byte_6F7D08[0] )
    return rf_gamesound_play_event(44, 0, 0.0, 1.0);
  else
    return rf_gamesound_play_event(45, 0, 0.0, 1.0);
}

