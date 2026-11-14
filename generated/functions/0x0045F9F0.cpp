// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045F9F0 rf_multiplayer_menu_request_join_panel30
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg,Join Game button binding verified by builder/native original label. If current pane661F8C!=-1,store pending=-1 and profile speed=-shared open speed.
// Always request deferred UI panel30 with(30,0,0),then disable profile input/hide460550. Does not immediately change current pane,commit edited name or start network join in body. No
// own active-session/runtime admission;builder state9 and navigation/hit test supply UI admission. EAX incidental.
void rf_multiplayer_menu_request_join_panel30()
{
  if ( dword_661F8C != -1 )
  {
    dword_661F90 = -1;
    unk_6F4864 = -rf_ui_open_transition_speed;
  }
  rf_ui_request_panel_deferred(30, 0, 0);
  rf_multiplayer_profile_disable_input_and_schedule_hide();
}

