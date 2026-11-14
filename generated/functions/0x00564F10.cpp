// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564F10 rf_model_handle_prepare_materials_if_nonnull
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Only tests handle pointer nonnull before calling5629C0 prepare-resources dispatch. Null path leaves EAX unspecified; nonnull delegate has no common semantic return. Does not load a handle, warm geometry directly, or validate tag/instance.
void __cdecl rf_model_handle_prepare_materials_if_nonnull(_DWORD *a1)
{
  if ( a1 )
    rf_model_handle_prepare_material_resources(a1);
}

