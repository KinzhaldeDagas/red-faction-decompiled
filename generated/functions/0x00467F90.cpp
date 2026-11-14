// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467F90 rf_options_menu_pane_input_enable
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Set raw BYTE6F6000=1 only. No current/pendingpane,position,velocity,focus or sound mutation. Routing separately checks current pane,so input can be
// enabled before transition commits. No defined EAX status.
void rf_options_menu_pane_input_enable()
{
  byte_6F6000[0] = 1;
}

