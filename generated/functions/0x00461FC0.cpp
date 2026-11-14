// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00461FC0 rf_browser_sort_by_players
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. Store sort modeDWORD661FE0=4,then rebuild filtered/sorted row indices461B60. No sort-direction toggle,scroll reset,disk write or packet send. Comparator4613B0 owns
// ordering/ties;repeated same-header click retains same mode. No uniform useful EAX status.
void rf_browser_sort_by_players()
{
  dword_661FE0 = 4;
  rf_browser_rebuild_filtered_sorted_row_indices();
}

