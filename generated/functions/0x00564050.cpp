// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564050 rf_model_handle_load_v3m_mode0
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Same pooled88byte V3M factory as563EC0, normalizing limit-1 to9999999, but passes loader mode0. V3M loader does not use this mode, so no instance/definition distinction actually follows from it. Sets material80=0 on success; destroys handle and returnsNULL if loader reports failure. Shared asset remains cache-owned.
void *__cdecl rf_model_handle_load_v3m_mode0(const char *a1, unsigned __int8 a2, int a3)
{
  _DWORD *initialized; // [esp+0h] [ebp-4h]

  if ( a3 == -1 )
    a3 = (int)byte_98967F;
  initialized = rf_model_handle_allocate_initialized();
  if ( rf_vmesh_type1_v3m_load(initialized, (char *)a1, a2, 0, a3) )
  {
    initialized[20] = 0;
  }
  else
  {
    rf_model_handle_destroy_and_release_to_pool(initialized);
    return nullptr;
  }
  return initialized;
}

