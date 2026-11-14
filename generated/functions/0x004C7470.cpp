// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C7470 rf_glass_commit_queued_geometry_when_boolean_idle
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, full rectangular/general quad tessellation, ordered edge selection and stale loop indices, native UV/grid coordinates, pool freshness and delayed launch semantics): 
// Cdecl no args. Queries geomod_boolean_is_active AL; nonzero returns without draining queue. When idle iterates pointer array823B68, re-reading current count each iteration, passes
// each queued owner/geometry pointer to74D0(remove_geometry_and_record_id), then releases pointer-array STORAGE (not only count) via517F40. Does not clear persisted removed-ID
// snapshot registry, release shards/texture, or validate queue elements. EAX pointer-shaped release/active-query artifact, not processed count/success.
void **rf_glass_commit_queued_geometry_when_boolean_idle()
{
  void **result; // eax
  int *v1; // eax
  int i; // [esp+0h] [ebp-4h]

  result = (void **)rf_geomod_boolean_is_active();
  if ( !(_BYTE)result )
  {
    for ( i = 0; i < rf_receiver_get_first_dword(unk_823B68); ++i )
    {
      v1 = (int *)sub_552200(unk_823B68, i);
      rf_glass_remove_geometry_and_record_id(*v1);
    }
    return rf_pointer_array_release_storage((void **)unk_823B68);
  }
  return result;
}

