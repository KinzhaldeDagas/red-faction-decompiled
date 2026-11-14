// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459DE0 rf_main_menu_continue_to_multiplayer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. If previous-panel-nonzero snapshot byte is ZERO, call4480B0 preparation; any nonzero skips it. Then unconditionally request deferred panel15 with
// flags1,1 via446460; cleanup12, BYTE661E88=0, close459060. Does not gate close/state clear on request success or normalize final EAX.
int rf_main_menu_continue_to_multiplayer()
{
  if ( !rf_main_menu_has_previous_panel )
    rf_prepare_multiplayer_menu_without_session();
  rf_ui_request_panel_deferred(15, 1, 1);
  byte_661E88 = 0;
  return rf_main_menu_begin_close_transition();
}

