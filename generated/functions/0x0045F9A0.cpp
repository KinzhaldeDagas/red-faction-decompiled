// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045F9A0 rf_multiplayer_menu_toggle_profile_pane
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Current paneDWORD661F8C!=0 (including-1):pending pane661F90=0,profile speed6F4864=-shared open_vertical_speed,enable profile input460540. Current pane
// EXACT0:pending=-1,write shared open speed,then disable/hide460550;that helper overwrites speed with NEGATED open speed because current!= -1. Thus both normal branches finish with
// negated shared speed;input flag distinguishes desired open/close. Current pane itself unchanged until animation endpoint commits. No name commit,panel request,sound or runtime
// admission. Stored int return incidental.
void rf_multiplayer_menu_toggle_profile_pane()
{
  if ( dword_661F8C )
  {
    dword_661F90 = 0;
    unk_6F4864 = -rf_ui_open_transition_speed;
    rf_multiplayer_profile_input_enable();
  }
  else
  {
    dword_661F90 = -1;
    unk_6F4864 = rf_ui_open_transition_speed;
    rf_multiplayer_profile_disable_input_and_schedule_hide();
  }
}

