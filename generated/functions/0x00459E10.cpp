// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459E10 rf_main_menu_open_options_panel
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Requests deferred panel14 via446460 with flags0,0 BEFORE clearing BYTE661E88 and invoking459060 close. Caller cleanup12; final EAX from close
// helper. No immediate panel switch, options write, admission-result guard or rollback.
int rf_main_menu_open_options_panel()
{
  rf_ui_request_panel_deferred(14, 0, 0);
  byte_661E88 = 0;
  return rf_main_menu_begin_close_transition();
}

