// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045CED0 rf_multiplayer_setup_next_game_mode
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Next-choice helper471E70(ECXcontrol6F3458),sound46(0,0.0,1.0),apply mode-control state9 flags,then rebuild
// filtered levels/clear rotation selection45CD00. No changed-mode test or registry write here. Next helper increments and signed-wraps at count;EAX is final rebuild residue,not
// mode/success. Sound46 is native for this right/next wrapper.
int rf_multiplayer_setup_next_game_mode()
{
  rf_ui_choice_cycle_next((int)dword_6F3458);
  rf_gamesound_play_event(46, 0, 0.0, 1.0);
  rf_multiplayer_setup_apply_mode_control_flags(unk_6F35C4);
  return rf_multiplayer_setup_rebuild_filtered_level_list();
}

