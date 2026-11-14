// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459C80 rf_main_menu_open_save_panel
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Calls459060 begin-close transition before446460(panel7,0,0). Caller removes12 outgoing bytes, forwards EAX without normalization. No own
// readiness/admission guard, immediate save operation or rollback; panel identifier differs from459C60 only in literal7 versus6.
int rf_main_menu_open_save_panel()
{
  rf_main_menu_begin_close_transition();
  return rf_ui_request_panel_deferred(7, 0, 0);
}

