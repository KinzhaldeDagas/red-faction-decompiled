// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565150 rf_model_handle_scene_payload_flags_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,index,payload,flags) forwards corrected thiscall563800. No incoming EDX argument or additional bit-mask policy; return raw bits.
unsigned int __cdecl rf_model_handle_scene_payload_flags_adapter(void *a1, int a2, int a3, unsigned int a4)
{
  return rf_model_handle_set_scene_node_payload_flags(a1, a2, a3, a4);
}

