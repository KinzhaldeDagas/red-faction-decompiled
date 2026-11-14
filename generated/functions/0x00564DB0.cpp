// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564DB0 rf_model_handle_named_sphere_count_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl handle forwards named-sphere count562240. Tags1/2 supported,other tags0; no pose evaluation.
int __cdecl rf_model_handle_named_sphere_count_adapter(_DWORD *a1)
{
  return rf_model_handle_get_named_sphere_count(a1);
}

