// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A530 rf_level_browser_clear_panel_request
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Cdecl no arguments, ten-byte wrapper calling rf_ui_clear_panel_request. Requests panel clear through delegate, no direct browser destruction or level loading; returns void.
void rf_level_browser_clear_panel_request()
{
  rf_ui_request_panel_stack_pop();
}

