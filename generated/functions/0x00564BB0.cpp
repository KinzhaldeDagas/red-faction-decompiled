// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564BB0 rf_model_handle_render_all_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,position,orientation,options). Forwards indexed renderer5642A0 with index-1. No validation or state restoration of its own; inherits temporary material swaps, scene draw ordering and raw return.
int *__cdecl rf_model_handle_render_all_adapter(int *a1, int a2, float *a3, int a4)
{
  return rf_model_handle_render_indexed_dispatch(a1, -1, a2, a3, a4);
}

