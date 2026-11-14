// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DA30 rf_multiplayer_menu_get_max_players
// UNREALRED VERIFIED [local-multiplayer-20261028] Returns dword table0x661EF8[selected index]. Ten PE-matched host player-count choices are2,3,4,6,8,10,12,16,24,32. Server options initialization0x45BCD0 sets index4 on first construction, selecting8 players.
int rf_multiplayer_menu_get_max_players()
{
  return rf_multiplayer_host_player_count_choices[unk_6F395C];
}

