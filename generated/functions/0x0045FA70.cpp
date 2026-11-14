// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045FA70 rf_multiplayer_menu_request_back
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg,Back binding. If current pane!=-1,pending=-1 and negative shared profile speed;call UI clear_panel_request,then disable/hide profile460550. Does not
// directly commit name,change current pane or stop multiplayer runtime. Existing int return incidental. Escape router also passes two ignored extra stack words before this noarg
// call;native body consumes none.
void rf_multiplayer_menu_request_back()
{
  if ( dword_661F8C != -1 )
  {
    dword_661F90 = -1;
    unk_6F4864 = -rf_ui_open_transition_speed;
  }
  rf_ui_request_panel_stack_pop();
  rf_multiplayer_profile_disable_input_and_schedule_hide();
}

