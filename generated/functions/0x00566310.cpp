// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566310 rf_model_handle_get_first_model_container
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Tag1 returns collection pointer4;tag2 returns embedded FIRST LOD container at definition8+6592 through no-op vector constructor;other tagsNULL. Does not select current visual LOD or return an animated character instance. No allocation/initialization/validation.
void *__cdecl rf_model_handle_get_first_model_container(_DWORD *a1)
{
  if ( *a1 == 1 )
    return (void *)a1[1];
  if ( *a1 == 2 )
    return rf_vector3_default_construct_noop((void *)(a1[2] + 6592));
  return nullptr;
}

