// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00469C80 rf_performance_preset_cycle_previous
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Noarg. Cycle preset chooser6F75A0 PREVIOUS,apply raw selectedDWORD6F770C via469A50,then sound46. Bound RIGHT arrow6F7AA0. No changed-choice
// guard,input/runtime/player validation or file save. Apply argument slot reused for sound gain;native ABI preserved.
int rf_performance_preset_cycle_previous()
{
  rf_ui_choice_cycle_previous(dword_6F75A0);
  rf_performance_options_apply_preset(unk_6F770C);
  return rf_gamesound_play_event(46, 0, 0.0, 1.0);
}

