// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566990 rf_model_handle_release_asset_then_destroy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Tag1 calls explicit V3C cache removal on asset4;tag2 character cache-release wrapper on definition8;tag3 scene cache removal on definition8. THEN always destroys/pool-releases handle563F70,including owned runtime instance/materials. No shared-reference checks, not-found validation or deferral in this dispatcher; cache removers ignore retained status and have unconditional decrement behavior.
_DWORD *__cdecl rf_model_handle_release_asset_then_destroy(int *a1)
{
  int v2; // [esp+0h] [ebp-8h]

  v2 = *a1;
  if ( *a1 == 1 )
  {
    rf_v3c_cache_remove_pointer_unchecked((char *)a1[1]);
  }
  else if ( v2 == 2 )
  {
    rf_character_cache_release_record_wrapper(a1[2]);
  }
  else if ( v2 == 3 )
  {
    rf_scene_cache_remove_pointer_unchecked((char *)a1[2]);
  }
  return rf_model_handle_destroy_and_release_to_pool(a1);
}

