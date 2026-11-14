// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045CFA0 rf_multiplayer_setup_next_player_count_choice
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Next-choice471E70 ECX=6F37F0,then always sound46(0,0.0,1.0). No level-list/rotation mutation,registry write
// or changed-choice admission. Delegate owns selected-index wrapping;numeric max-player value retrieved separately45DA30. Return sound result residue.
int rf_multiplayer_setup_next_player_count_choice()
{
  rf_ui_choice_cycle_next((int)dword_6F37F0);
  return rf_gamesound_play_event(46, 0, 0.0, 1.0);
}

