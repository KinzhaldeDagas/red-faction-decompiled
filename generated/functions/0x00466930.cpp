// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00466930 rf_host_menu_request_back
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg. Set pending pane6F5E3C=-1,paneX speed6F5E4C=-shared open speed,then clear UI panel request. Does not explicitly disable pane-input6F5E29,persist LAN
// settings or stop multiplayer;driver/leave delegates own remainder. Keyboard may pass two ignored sentinel words.
void rf_host_menu_request_back()
{
  unk_6F5E3C = -1;
  unk_6F5E4C = -rf_ui_open_transition_speed;
  rf_ui_request_panel_stack_pop();
}

