// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564DF0 rf_model_handle_get_named_sphere_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,index,outCenter,outRadius) forwards562310 and returns byte result. Tag2 center animated by bone transform, radius unscaled; failure leaves outputs unchanged.
char __cdecl rf_model_handle_get_named_sphere_adapter(_DWORD *a1, int a2, float *a3, float *a4)
{
  return rf_model_handle_get_named_sphere_position_radius(a1, a2, a3, a4);
}

