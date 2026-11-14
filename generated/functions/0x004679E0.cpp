// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004679E0 rf_options_menu_toggle_controls_pane
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Current paneDWORD661FF4==EXACT3 ->disable pane input/schedule hide467FA0. Otherwise set pending pane661FF8=3,paneXspeed6F6028=-shared open speed,enable
// pane input467F90. Current pane unchanged until animation upper endpoint commits. No own build,settings apply,save,sound or input/main-menu gate. Shared speed named vertical drives
// logical X;existing int return incidental.
void rf_options_menu_toggle_controls_pane()
{
  if ( dword_661FF4 == 3 )
  {
    rf_options_menu_disable_pane_input_and_hide();
  }
  else
  {
    dword_661FF8 = 3;
    unk_6F6028 = -rf_ui_open_transition_speed;
    rf_options_menu_pane_input_enable();
  }
}

