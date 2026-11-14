// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FBE20 rf_scene_material_cursor_context_destruct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VSFX header/version gates, pool ownership/cursors, FourCC dispatch, normal error cleanup and model postprocessing): No-op local material-pool cursor context destructor. VSFX cleanup supplies context ECX but body ignores it and does not free materials/index buffers, reset fields or call anything. EAX untouched, existing library flag retained. Distinct from owning scene destructor5CA7D0.
void rf_scene_material_cursor_context_destruct_noop()
{
  ;
}

