// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004666B0 rf_host_menu_toggle_rules_pane
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg. Current pane6F5E30==EXACT1:disable input/schedule hide467320. Otherwise pending pane6F5E3C=1,paneX speed6F5E4C=-shared open speed,enable
// input467310. Current pane changes later at animation upper endpoint;no own rules apply,construction or sound.
void rf_host_menu_toggle_rules_pane()
{
  if ( unk_6F5E30 == 1 )
  {
    rf_host_menu_disable_pane_input_and_hide();
  }
  else
  {
    unk_6F5E3C = 1;
    unk_6F5E4C = -rf_ui_open_transition_speed;
    rf_host_menu_pane_input_enable();
  }
}

