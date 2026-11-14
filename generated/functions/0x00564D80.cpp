// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564D80 rf_model_handle_get_node_transform_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,outPosition,outMatrix,index) forwards562050. No new checks; delegate byte return can be pointer-low-byte/incidental rather than success. Kind1 scene subobject leaves outputs untouched.
char __cdecl rf_model_handle_get_node_transform_adapter(_DWORD *a1, float *a2, float *a3, int a4)
{
  return rf_model_handle_get_node_transform(a1, a2, a3, a4);
}

