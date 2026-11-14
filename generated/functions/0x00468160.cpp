// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00468160 rf_controls_change_selected_binding
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg,Change Binding button callback. ALWAYS ensure selected action visible468180 first. Only captureDWORD6F62B4==0 begins capture467FE0;other nonzero values
// left unchanged. No selected-index/player/count validation,binding mutation,sound or persistence.
void rf_controls_change_selected_binding()
{
  rf_controls_ensure_selected_action_visible();
  if ( !unk_6F62B4 )
    rf_controls_binding_capture_begin();
}

