// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459B80 rf_main_menu_start_training
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Calls459BB0 with literal train01.rfl, caller cleanup4, then45A0F0 guarded owned-music stop, writes BYTE661E88=0 and calls459060 close. Returns
// final delegate EAX. Does not test level-request return, stop return, active-session state or roll back earlier effects.
int rf_main_menu_start_training()
{
  rf_main_menu_queue_level_load("train01.rfl");
  rf_main_menu_stop_owned_music();
  byte_661E88 = 0;
  return rf_main_menu_begin_close_transition();
}

