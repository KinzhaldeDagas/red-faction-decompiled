// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459E80 rf_main_menu_quit_application_yes
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Calls446100(action17,force0), cleanup8, then BYTE661E88=0 and459060 close regardless of request return. Forwards close EAX; actual
// application-exit dispatch is not performed in this wrapper.
int rf_main_menu_quit_application_yes()
{
  rf_ui_request_panel_immediate(17, 0);
  byte_661E88 = 0;
  return rf_main_menu_begin_close_transition();
}

