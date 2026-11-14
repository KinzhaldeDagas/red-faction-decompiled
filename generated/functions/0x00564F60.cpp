// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564F60 rf_model_handle_set_cyclic_mix_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,action,mix) forwards562A70. Character updates cyclic record mix; scene uses only exact-zero/nonzero float to set stop/mode2 flags and reset clocks.
int *__cdecl rf_model_handle_set_cyclic_mix_adapter(int *a1, int a2, float a3)
{
  return rf_model_handle_set_cyclic_mix_or_scene_mode2(a1, a2, a3);
}

