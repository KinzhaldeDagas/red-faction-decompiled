// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045CE90 rf_multiplayer_setup_previous_game_mode
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Previous-choice helper471EC0(control6F3458),then sound47(0,0.0,1.0),apply state9 controls45F7F0(current
// mode6F35C4),then rebuild filtered levels45CD00. Helper wraps decrement for nonzero choice count. No saved old-mode comparison:rebuild clears rotation selection even if choice did
// not change. Return rebuild residue,not chosen mode. Native left/previous uses sound47 (not inferred from arrow convention).
int rf_multiplayer_setup_previous_game_mode()
{
  rf_ui_choice_cycle_previous(dword_6F3458);
  rf_gamesound_play_event(47, 0, 0.0, 1.0);
  rf_multiplayer_setup_apply_mode_control_flags(unk_6F35C4);
  return rf_multiplayer_setup_rebuild_filtered_level_list();
}

