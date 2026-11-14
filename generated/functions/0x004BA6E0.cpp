// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BA6E0 rf_world_object_handle_render_callback
// UNREALRED VERIFIED [impact-callbacks-20261028]: Resolves caller runtime object handle through rf_object_resolve_handle, passes resulting pointer (includingnull) to0x4BA710. Returns low byte of renderer result. No independent existence,visibility or room check in wrapper; downstream handles policy.
char __cdecl rf_world_object_handle_render_callback(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_object_resolve_handle(a1);
  return rf_object_render_one_type_dispatch(v2);
}

