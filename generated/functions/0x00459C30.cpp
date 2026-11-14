// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459C30 rf_main_menu_start_campaign
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Same sequence as459B80 with literal l1s1.rfl: queue level request459BB0, stop owned menu music45A0F0, BYTE661E88=0, close459060. No own
// admission guard, return-status test or rollback; final EAX is close helper residue.
int rf_main_menu_start_campaign()
{
  rf_main_menu_queue_level_load("l1s1.rfl");
  rf_main_menu_stop_owned_music();
  byte_661E88 = 0;
  return rf_main_menu_begin_close_transition();
}

