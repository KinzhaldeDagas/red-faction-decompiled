// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045EE70 rf_multiplayer_rules_previous_capture_choice
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Noarg. Invoke verified choice-cycle previous helper withECX=control6F44A8;then ALWAYS gamesound event47(0,0.0,1.0),including empty-choice/no-change case. Delegate
// updates raw selected INDEX with its own signed wrap predicates. No mode/runtime/authority gate,gameplay-limit store,registry write,level-list/rotation reset or changed-choice test.
// Return soundEAX residue,not selected numeric rule value. Left/previous uses47,right/next46 by native pushes.
int rf_multiplayer_rules_previous_capture_choice()
{
  rf_ui_choice_cycle_previous(unk_6F44A8);
  return rf_gamesound_play_event(47, 0, 0.0, 1.0);
}

