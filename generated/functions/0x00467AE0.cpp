// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467AE0 rf_options_menu_hide_pane
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Call disable_pane_input_and_hide467FA0 only;no additional state,sound,save or panel request. Existing int return is incidental delegate residue.
void rf_options_menu_hide_pane()
{
  rf_options_menu_disable_pane_input_and_hide();
}

