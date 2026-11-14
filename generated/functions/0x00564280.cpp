// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564280 rf_model_handle_destroy_cdecl_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): False generic runtime identification:one cdecl handle arg is forwarded to563F70 destruction/pool release. No null guard or additional ownership logic; EAX returned from pool release.
_DWORD *__cdecl rf_model_handle_destroy_cdecl_adapter(_DWORD *a1)
{
  return rf_model_handle_destroy_and_release_to_pool(a1);
}

