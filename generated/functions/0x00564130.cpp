// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564130 rf_model_handle_load_character_definition_only
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Pooled handle factory calling character loader with createInstance0. Success retains definition8 but instance4NULL and material80=0; methods requiring runtime instance are not made valid by this path. Definition-load failure releases handle/returnsNULL. ExtraDWORD forwarded/unused; no direct cache ownership transfer.
void *__cdecl rf_model_handle_load_character_definition_only(const char *a1, unsigned __int8 a2, int a3)
{
  int *initialized; // [esp+0h] [ebp-4h]

  initialized = (int *)rf_model_handle_allocate_initialized();
  if ( rf_model_handle_load_character(initialized, (char *)a1, a2, 0, a3) )
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

