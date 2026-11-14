// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565EA0 rf_model_handle_disable_private_materials
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Writes only handle byte84=0 and returns handle bits. Does NOT free material80 array or clear pointer/count; re-enabling can reuse clone, and handle destruction still frees material80 regardless active flag.
void *__cdecl rf_model_handle_disable_private_materials(void *a1)
{
  *((_BYTE *)a1 + 84) = 0;
  return a1;
}

