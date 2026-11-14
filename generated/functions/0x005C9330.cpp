// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C9330 rf_scene_material_index_context_destruct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VSFX header/version gates, pool ownership/cursors, FourCC dispatch, normal error cleanup and model postprocessing): No-op destructor adapter for local24-byte material/index read context (5C92E0), also called in VSFX SEH/normal cleanup. No free, pool traversal, pointer reset, calls or memory access; supplied ECX ignored, EAX unchanged. Existing library flag retained.
void rf_scene_material_index_context_destruct_noop()
{
  ;
}

