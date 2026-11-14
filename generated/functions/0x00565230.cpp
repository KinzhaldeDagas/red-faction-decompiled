// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565230 rf_model_handle_scene_hidden_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,index,hiddenByte,propagateByte) forwards corrected thiscall563A90. Preserves low-bit hidden masking but exact-byte1 point release/propagation gates; no new recursion/cycle guard.
unsigned int __cdecl rf_model_handle_scene_hidden_adapter(void *a1, int a2, unsigned __int8 a3, unsigned __int8 a4)
{
  return rf_model_handle_set_scene_node_hidden(a1, a2, a3, a4);
}

