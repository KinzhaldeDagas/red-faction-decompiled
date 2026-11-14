// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005641A0 rf_vfx_load_instance
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Allocates88byte handle and type3VFX loader(filename,createInstance1,flags). Success sets material80=0 and returns handle; reported failure releases handle/NULL. Scene loader may report success with instanceNULL on allocation failure, and its definition cache loader can invoke fatal error on missing/corrupt file. No validation/catch added here.
int *__cdecl rf_vfx_load_instance(char *a1, int a2)
{
  int *initialized; // [esp+0h] [ebp-4h]

  initialized = (int *)rf_model_handle_allocate_initialized();
  if ( rf_vmesh_type3_vfx_load(initialized, a1, 1, a2) )
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

