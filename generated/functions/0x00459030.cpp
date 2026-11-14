// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459030 rf_main_menu_quit_current_game_yes
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments/receiver use in native body. Calls48ED40 multiplayer teardown, then446100(action13,force0); regardless of returned request status sets
// restart-music DWORD1 and BYTE661E88=0, then calls459060 close transition. Returns final delegate EAX. No rollback, immediate process exit, or request-success gate.
int __thiscall rf_main_menu_quit_current_game_yes(void *this)
{
  rf_multiplayer_runtime_teardown();
  rf_ui_request_panel_immediate(13, 0);
  rf_main_menu_restart_music_pending = 1;
  byte_661E88 = 0;
  return rf_main_menu_begin_close_transition();
}

