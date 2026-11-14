// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565020 rf_model_handle_reset_actions_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl handle forwards562DC0 action reset. Does not call cyclic-only reset5877B0; scene stop/reset flags and clocks inherited.
int *__cdecl rf_model_handle_reset_actions_adapter(int *a1)
{
  return rf_model_handle_reset_action_animations(a1);
}

