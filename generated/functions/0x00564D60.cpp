// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564D60 rf_model_handle_find_node_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,name) forwards model-handle name lookup. Inherits tag1 case-insensitive prefix,tag2 character lookup,tag3 exact case-insensitive scene-name comparison and inconsistent null handling.
int __cdecl rf_model_handle_find_node_adapter(_DWORD *a1, char *String2)
{
  return rf_model_handle_find_node_by_name(a1, String2);
}

