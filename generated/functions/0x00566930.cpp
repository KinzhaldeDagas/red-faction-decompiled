// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566930 rf_model_handle_mark_asset_retained
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Tag1 marks cache asset4 bit1,tag2 marks character definition8 retained,tag3 marks scene definition8 bit1;unknown no change. No reference increment, per-handle flag, ownership transfer or resource load; raw return helper/handle bits.
int *__cdecl rf_model_handle_mark_asset_retained(int *a1)
{
  int *result; // eax
  int v2; // [esp+0h] [ebp-8h]

  result = a1;
  v2 = *a1;
  if ( *a1 == 1 )
    return (int *)rf_v3c_cache_mark_asset_retained(a1[1]);
  if ( v2 == 2 )
    return (int *)rf_character_cache_mark_record_retained(a1[2]);
  if ( v2 == 3 )
    return (int *)rf_scene_cache_mark_definition_retained(a1[2]);
  return result;
}

