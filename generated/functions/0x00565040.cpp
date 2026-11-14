// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565040 rf_model_handle_zero_action_weight_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,action) forwards562E40:character zero specific weight; scene resets whole action state. No independent index/null validation.
int *__cdecl rf_model_handle_zero_action_weight_adapter(float **a1, int a2)
{
  return rf_model_handle_zero_action_weight(a1, a2);
}

