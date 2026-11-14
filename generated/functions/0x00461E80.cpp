// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00461E80 rf_browser_mode_filter_previous
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. Cycle chooser6F5828 previous,play sound47(0,0.0,1.0),then rebuild filtered/sorted display indices461B60. No changed-choice guard,scroll reset or packet send. Rebuild
// owns selection reconciliation;return residue.
void rf_browser_mode_filter_previous()
{
  rf_ui_choice_cycle_previous(unk_6F5828);
  rf_gamesound_play_event(47, 0, 0.0, 1.0);
  rf_browser_rebuild_filtered_sorted_row_indices();
}

