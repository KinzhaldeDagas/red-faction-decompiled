// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564210 rf_model_handle_load_scene_definition_only
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Allocates88byte handle and calls VFX loader with createInstance0. Success stores tag3 definition8,instance4NULL,material80=0. Reported failure releases handle and returnsNULL. Definition cache retains ownership; runtime-only handle APIs receive no substitute instance here.
void *__cdecl rf_model_handle_load_scene_definition_only(const char *a1, int a2)
{
  int *initialized; // [esp+0h] [ebp-4h]

  initialized = (int *)rf_model_handle_allocate_initialized();
  if ( rf_vmesh_type3_vfx_load(initialized, (char *)a1, 0, a2) )
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

