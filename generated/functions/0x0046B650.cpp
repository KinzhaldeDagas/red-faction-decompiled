// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B650 rf_gameplay_difficulty_choice_previous
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Noarg. Cycle chooser6F7DE8 PREVIOUS,then sound47(0,0.0,1.0);bound to left arrow. Selected stateDWORD6F7F54 changes through chooser only. NO direct
// player/renderer/difficulty commit,Custom marking,preset apply,changed-choice guard or file save. Parent group wrapper owns commit;calling this leaf directly bypasses it. Existing
// return sound residue;no key/index/runtime admission.
int rf_gameplay_difficulty_choice_previous()
{
  rf_ui_choice_cycle_previous(dword_6F7DE8);
  return rf_gamesound_play_event(47, 0, 0.0, 1.0);
}

