// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00563F70 rf_model_handle_destroy_and_release_to_pool
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Requires nonnull handle. Tag2 deletes nonnull character instance4 with flags1;tag3 deletes nonnull scene instance4 via566C30 flags1;clears instance4 after those. Tag1 cached asset4 is NOT deleted here. If material pointer80 nonnull, invokes200byte material vector-deleting adapter566A00 flags3 regardless byte84. Finally pushes handle onto global88byte pool free list. Definition/cache pointers and filename not explicitly released/cleared; no double-release guard.
_DWORD *__cdecl rf_model_handle_destroy_and_release_to_pool(_DWORD *a1)
{
  if ( *a1 == 2 )
  {
    if ( a1[1] )
    {
      rf_character_instance_scalar_deleting_destructor((int *)a1[1], 1);
      a1[1] = 0;
    }
  }
  else if ( *a1 == 3 && a1[1] )
  {
    rf_scene_instance_scalar_deleting_destructor((void *)a1[1], 1);
    a1[1] = 0;
  }
  if ( a1[20] )
    rf_material200_vector_deleting_destructor((char *)a1[20], 3);
  return rf_model_handle88_pool_release_raw(dword_17F1120, a1);
}

