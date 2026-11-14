// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467FA0 rf_options_menu_disable_pane_input_and_hide
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Clear paneInputBYTE6F6000. If currentPane661FF4!=-1,set pending661FF8=-1 and paneXspeed6F6028=-shared open speed. Already current-1 preserves
// pending/speed. No immediate current-pane/coordinate change,save,binding-capture reset or sound. Pending pane transition committed in animation routine.
void rf_options_menu_disable_pane_input_and_hide()
{
  byte_6F6000[0] = 0;
  if ( dword_661FF4 != -1 )
  {
    dword_661FF8 = -1;
    unk_6F6028 = -rf_ui_open_transition_speed;
  }
}

