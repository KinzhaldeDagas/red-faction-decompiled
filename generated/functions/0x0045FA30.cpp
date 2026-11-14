// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045FA30 rf_multiplayer_menu_request_create_panel32
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg,Create Game binding from builder. If current pane!=-1,schedule pending=-1 and negative shared profile speed;always deferred request
// panel32(32,0,0),then460550 clears profile input and schedules hide if needed. No actual server creation,settings apply,edited-name commit or own active-session/runtime check in
// body. Current pane waits for animation endpoint.
void rf_multiplayer_menu_request_create_panel32()
{
  if ( dword_661F8C != -1 )
  {
    dword_661F90 = -1;
    unk_6F4864 = -rf_ui_open_transition_speed;
  }
  rf_ui_request_panel_deferred(32, 0, 0);
  rf_multiplayer_profile_disable_input_and_schedule_hide();
}

