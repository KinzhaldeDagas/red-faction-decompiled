// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564E20 rf_model_handle_get_named_sphere_world_center
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,index,outCenter,translation,orientation). Queries named sphere into outCenter and LOCAL radius; failure0. On success rotates center in place by supplied matrix then adds translation,returns1. Radius discarded, no world-radius/scale output or transform validation.
char __cdecl rf_model_handle_get_named_sphere_world_center(_DWORD *a1, int a2, float *a3, float *a4, float *a5)
{
  float v6; // [esp+4h] [ebp-4h] BYREF

  if ( !rf_model_handle_get_named_sphere_position_radius(a1, a2, a3, &v6) )
    return 0;
  rf_vector_rotate_by_matrix3(a3, a5);
  rf_vector_accumulate(a3, a4);
  return 1;
}

