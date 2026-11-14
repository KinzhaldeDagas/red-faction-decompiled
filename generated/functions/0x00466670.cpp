// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00466670 rf_host_menu_toggle_setup_pane
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg. Current paneDWORD6F5E30!=EXACT0 (including-1):set pending pane6F5E3C=0,paneX speed6F5E4C=-shared open speed,enable pane input467310. Current
// pane0:disable pane input/schedule hide467320. Does not immediately change current pane or call setup builder;animation upper endpoint commits pending. Caller may pass ignored
// coordinate words. No sound here.
void rf_host_menu_toggle_setup_pane()
{
  if ( unk_6F5E30 )
  {
    unk_6F5E3C = 0;
    unk_6F5E4C = -rf_ui_open_transition_speed;
    rf_host_menu_pane_input_enable();
  }
  else
  {
    rf_host_menu_disable_pane_input_and_hide();
  }
}

