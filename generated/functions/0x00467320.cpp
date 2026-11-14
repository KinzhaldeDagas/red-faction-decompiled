// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467320 rf_host_menu_disable_pane_input_and_hide
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg. Clear paneInputBYTE6F5E29. If currentPane6F5E30!=-1,set pendingPane6F5E3C=-1 and paneX speed6F5E4C=-shared open speed. Current-1 preserves prior
// pending/speed. No immediate current change,coordinate clamp,persistence,apply or sound. Can overwrite a caller's preceding pane-speed0 assignment.
void rf_host_menu_disable_pane_input_and_hide()
{
  unk_6F5E29 = 0;
  if ( unk_6F5E30 != -1 )
  {
    unk_6F5E3C = -1;
    unk_6F5E4C = -rf_ui_open_transition_speed;
  }
}

