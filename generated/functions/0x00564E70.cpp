// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564E70 rf_model_handle_bounds_sphere_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,outCenter,outRadius) forwards whole-handle sphere562420. No return/status, output initialization or extra center transform.
void __cdecl rf_model_handle_bounds_sphere_adapter(_DWORD *a1, float *a2, float *a3)
{
  rf_model_handle_get_bounds_sphere(a1, a2, a3);
}

