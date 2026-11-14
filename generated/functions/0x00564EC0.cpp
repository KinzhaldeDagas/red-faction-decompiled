// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564EC0 rf_model_handle_bounds_aabb_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,outMin,outMax) forwards562880. Inherits scene origin-centered radius cube and static reference mesh bounds for characters; raw return forwarded.
int __cdecl rf_model_handle_bounds_aabb_adapter(_DWORD *a1, float *a2, float *a3)
{
  return rf_model_handle_get_bounds_aabb(a1, a2, a3);
}

