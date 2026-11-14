// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00466E80 rf_host_menu_leave_and_persist_lan
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Cdecl immediateLOWBYTE. Nonzero:force titleX6F5E44=6F29C4,paneX6F5E2C=6F29C8,buttonX6F5E38=closedX and zero respective speeds6F5E48/4C/40. Zero:begin close
// animation466590/sound48. Both persist LAN-only setup via its verified delegate,call verified noop45F0B0,clear mainInput6F5E28. Does not directly clear
// paneInput6F5E29,current/pendingpane,stop runtime or commit other server settings;instant path skips sound. Existing type retained.
void __cdecl rf_host_menu_leave_and_persist_lan(char a1)
{
  if ( a1 )
  {
    unk_6F5E44 = (float)unk_6F29C4;
    unk_6F5E48 = 0.0;
    unk_6F5E2C = (float)unk_6F29C8;
    unk_6F5E4C = 0.0;
    unk_6F5E38 = (float)rf_main_menu_closed_x;
    unk_6F5E40 = 0.0;
  }
  else
  {
    rf_host_menu_begin_close_animation();
  }
  rf_multiplayer_setup_persist_lan_only();
  rf_ui_noop_callback_45F0B0();
  unk_6F5E28 = 0;
}

