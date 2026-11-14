// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459E30 rf_main_menu_open_extras_panel
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Requests deferred panel3 via446460 with flags0,0; cleanup12, clear BYTE661E88, close459060 and forward final EAX. Same order as459E10,
// differing panel literal. No immediate panel construction or request-result guard.
int rf_main_menu_open_extras_panel()
{
  rf_ui_request_panel_deferred(3, 0, 0);
  byte_661E88 = 0;
  return rf_main_menu_begin_close_transition();
}

