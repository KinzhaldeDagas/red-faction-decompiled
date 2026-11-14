// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564F30 rf_vfx_update_instance
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,dt,byteFlag,position,orientation,extraDWORD) forwards562A10 animation dispatch. Tag3 scene update uses dt and transform,tag2 character update uses dt/byteFlag/extra. Name does not restrict accepted tags; no added checks.
char __cdecl rf_vfx_update_instance(int *a1, float a2, char a3, float *a4, float *a5, int a6)
{
  return rf_model_handle_advance_animation_dispatch(a1, a2, a3, a4, a5, a6);
}

