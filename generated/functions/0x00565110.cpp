// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565110 rf_model_handle_parent_name_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,index) forwards563700 borrowed parent-name pointer. Tags1/2 literal Scene Root,tag3 record+65; no copying or allocation.
const char *__cdecl rf_model_handle_parent_name_adapter(const void *a1, int a2)
{
  return rf_model_handle_get_parent_name(a1, a2);
}

