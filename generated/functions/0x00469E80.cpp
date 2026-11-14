// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00469E80 rf_performance_character_detail_choice_previous
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Noarg. Cycle chooser6F7398 PREVIOUS,then sound46(0,0.0,1.0);bound to right arrow. Selected stateDWORD6F7504 changes through chooser only. NO direct
// player/renderer/difficulty commit,Custom marking,preset apply,changed-choice guard or file save. Parent group wrapper owns commit;calling this leaf directly bypasses it. Existing
// return sound residue;no key/index/runtime admission.
int rf_performance_character_detail_choice_previous()
{
  rf_ui_choice_cycle_previous(dword_6F7398);
  return rf_gamesound_play_event(46, 0, 0.0, 1.0);
}

