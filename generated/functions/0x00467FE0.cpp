// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467FE0 rf_controls_binding_capture_begin
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Set captureDWORD6F62B4=EXACT1,then replace help widget6F63A0 text with localized Press New Key88DEAC and font6F29AC. No selected-action/player/index/input
// validation,scroll update,key-buffer clear or binding write. Return text-surface delegate residue;mode isDWORD,notBYTE.
int *rf_controls_binding_capture_begin()
{
  unk_6F62B4 = 1;
  return rf_ui_modal_text_surface_initialize(dword_6F63A0, unk_88DEAC, unk_6F29AC);
}

