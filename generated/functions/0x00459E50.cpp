// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459E50 rf_main_menu_return_to_game
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Calls45A0F0 guarded music stop, then4464A0 deferred PANEL-STACK POP request. Sets restart-music DWORD1, clears BYTE661E88, calls459060 close
// and forwards EAX. This requests a stack pop, not merely clearing a pending panel request. No own empty-stack/admission guard or synchronous pop/teardown.
int rf_main_menu_return_to_game()
{
  rf_main_menu_stop_owned_music();
  rf_ui_request_panel_stack_pop();
  rf_main_menu_restart_music_pending = 1;
  byte_661E88 = 0;
  return rf_main_menu_begin_close_transition();
}

