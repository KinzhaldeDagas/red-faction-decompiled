// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00464AC0 rf_browser_request_back
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. Call rf_ui_clear_panel_request only. Does not itself persist caches,free lists,clear pendingIP or stop tracker;leave routine464EE0 owns those actions. Return delegate
// residue.
void rf_browser_request_back()
{
  rf_ui_request_panel_stack_pop();
}

