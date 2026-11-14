// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565130 rf_model_handle_node_count_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl handle forwards561EF0 type-specific node count. Unsupported tag-1; no cache refresh or allocation.
int __cdecl rf_model_handle_node_count_adapter(_DWORD *a1)
{
  return rf_model_handle_get_node_count(a1);
}

