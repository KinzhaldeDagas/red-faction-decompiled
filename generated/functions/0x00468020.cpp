// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00468020 rf_controls_binding_capture_end
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Set captureDWORD6F62B4=0,then help6F63A0=localized Select Action88DEA8 with font6F29AC. Does not modify selected bindings,scroll,paneInput/currentpane or
// persist configuration. Return delegate residue;called on successful binding and most keyboard rejections.
int *__cdecl rf_controls_binding_capture_end()
{
  unk_6F62B4 = 0;
  return rf_ui_modal_text_surface_initialize(dword_6F63A0, unk_88DEA8, unk_6F29AC);
}

