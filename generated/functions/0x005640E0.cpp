// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005640E0 rf_model_handle_load_character_instance
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Allocates initialized handle, calls561CD0(filename,cacheFlag,createInstance1,extraDWORD). On success sets material80=0 and returns handle; on definition-load failure destroys handle/NULL. Underlying character loader can report success with instance4NULL if allocation failed; factory adds no validation. ExtraDWORD forwarded but ignored by loader.
int *__cdecl rf_model_handle_load_character_instance(char *a1, char a2, int a3)
{
  int *initialized; // [esp+0h] [ebp-4h]

  initialized = (int *)rf_model_handle_allocate_initialized();
  if ( rf_model_handle_load_character(initialized, a1, a2, 1, a3) )
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

