// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005650F0 rf_model_handle_record_base_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,index) forwards563600 borrowed record-base lookup. Tag2 ignores index; scene decoder returns kind-specific base. Does not return allocated name string or validate bounds.
void *__cdecl rf_model_handle_record_base_adapter(const void *a1, int a2)
{
  return (void *)rf_model_handle_get_indexed_record_base(a1, a2);
}

