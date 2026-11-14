// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565000 rf_model_handle_reset_cyclic_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl handle forwards562D40 cyclic-animation reset. Scene branch matches action reset,character branch differs; no resource destruction.
int *__cdecl rf_model_handle_reset_cyclic_adapter(int *a1)
{
  return rf_model_handle_reset_cyclic_animations(a1);
}

