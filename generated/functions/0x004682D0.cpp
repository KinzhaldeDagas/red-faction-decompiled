// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004682D0 rf_controls_prompt_reset_defaults
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Show Yes/No modal with localized Control Config88E0CC,Reset All Controls88E0D0,Yes callback468200,NoNULL,extra0:five native stack words. Does not apply
// defaults until Yes callback,no current-player/capture/input guard or immediate save. EAX modal delegate residue.
int rf_controls_prompt_reset_defaults()
{
  return rf_ui_show_yes_no_modal(unk_88E0CC, unk_88E0D0, (int)rf_controls_reset_bindings_and_mouse_defaults, 0, 0);
}

