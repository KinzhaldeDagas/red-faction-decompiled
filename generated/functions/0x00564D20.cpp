// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564D20 rf_model_handle_collide_all_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,query,result,initializeByte) forwards indexed collision with index-1. No output initialization beyond delegate; scene tag still always no hit.
char __cdecl rf_model_handle_collide_all_adapter(_DWORD *a1, void *a2, float *a3, unsigned __int8 a4)
{
  return rf_model_handle_collide_indexed_dispatch(a1, -1, a2, a3, a4);
}

