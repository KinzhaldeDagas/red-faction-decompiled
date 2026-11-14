// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564DD0 rf_model_handle_find_named_sphere_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,name) forwards sphere prefix search5622A0; no null/record validation in adapter.
// UNREALRED VERIFIED [combat-named-sphere-binding-20261112]: cdecl adapter forwards handle/name unchanged to5622A0 (call564DE1); node-name lookup is a separate API. Native name matching is not full-string equality.
int __cdecl rf_model_handle_find_named_sphere_adapter(_DWORD *a1, char *String2)
{
  return rf_model_handle_find_named_sphere_prefix(a1, String2);
}

