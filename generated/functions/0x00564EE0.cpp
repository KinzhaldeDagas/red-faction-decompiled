// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564EE0 rf_model_handle_indexed_bounds_aabb_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,index,outMin,outMax) forwards5628A0, no validation or layout correction. Scene sphere center remains discarded.
int __cdecl rf_model_handle_indexed_bounds_aabb_adapter(void *a1, int a2, float *a3, float *a4)
{
  return (int)rf_model_handle_get_indexed_bounds_aabb((float *)a1, a2, a3, a4);
}

