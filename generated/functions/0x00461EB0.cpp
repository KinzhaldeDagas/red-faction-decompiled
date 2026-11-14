// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00461EB0 rf_browser_mode_filter_next
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. Cycle chooser6F5828 next,play sound46(0,0.0,1.0),then rebuild filtered/sorted display indices. No changed-choice guard,scroll reset or network send. Does not reverse
// sort direction.
void rf_browser_mode_filter_next()
{
  rf_ui_choice_cycle_next((int)unk_6F5828);
  rf_gamesound_play_event(46, 0, 0.0, 1.0);
  rf_browser_rebuild_filtered_sorted_row_indices();
}

