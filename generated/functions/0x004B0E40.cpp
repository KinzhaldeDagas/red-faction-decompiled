// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B0E40 sub_4B0E40
// UNREALRED VERIFIED [lan-match-flow-20261028] Authority next-level begin called by 0x4485C0 after successful level load: calls conditional team-balancing helper 0x4B0950, sends packet 22 via 0x4A5820, sets gameflags bit 2 and clears ending bit 4. The score reset belongs to earlier MP level-initialization helper 0x48EF50, not to 0x4B0950.
unsigned int sub_4B0E40()
{
  unsigned int result; // eax

  rf_multiplayer_autobalance_teams_by_stats_word0();
  sub_4A5820();
  result = rf_multiplayer_game_flags | 2;
  rf_multiplayer_game_flags |= 2u;
  rf_multiplayer_game_flags &= ~4u;
  return result;
}

