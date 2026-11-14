// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045CF70 rf_multiplayer_setup_previous_player_count_choice
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Previous-choice471EC0 on6F37F0,then always sound47(0,0.0,1.0),including no-choice/no-change case. Does not
// write chosen numeric max-player value directly,rebuild levels,clear rotation or persist registry. Control selected INDEX is updated by delegate;getter45DA30 maps it through
// ten-entry player-count table. Return sound EAX residue.
int rf_multiplayer_setup_previous_player_count_choice()
{
  rf_ui_choice_cycle_previous(dword_6F37F0);
  return rf_gamesound_play_event(47, 0, 0.0, 1.0);
}

