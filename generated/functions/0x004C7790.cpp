// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C7790 rf_geomod_postcut_glass_shard_invalidate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, full rectangular/general quad tessellation, ordered edge selection and stale loop indices, native UV/grid coordinates, pool freshness and delayed launch semantics): 
// Cdecl cutPosition,cutRadius. Walks all circular buckets caching next BEFORE unlink/release. Only attachment-owner100==NULL AND STRICT ORDERED
// cutRadius>fast_distance(cutPosition,shard.center8): unlink7850 then pool_release7920(count--). No budget96 test: includes moving,delayed AND unattached resting nodes; settled
// attached nonzero100 retained. Equality/NaN/negative radius ordinary distance reject. Does not test faces/room/sphere radius, rearm launch or remove bucket keys; no geometry/texture
// deletion.
void __cdecl rf_geomod_postcut_glass_shard_invalidate(float *a1, float a2)
{
  int v3; // [esp+0h] [ebp-10h]
  int j; // [esp+4h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < rf_glass_shard_bucket_count; ++i )
  {
    for ( j = rf_glass_shard_bucket_heads[2 * i]; j; j = v3 )
    {
      if ( *(_DWORD *)j == rf_glass_shard_bucket_heads[2 * i] )
        v3 = 0;
      else
        v3 = *(_DWORD *)j;
      if ( !*(_DWORD *)(j + 100) && a2 > rf_vector_fast_distance(a1, (const float *)(j + 8)) )
      {
        rf_glass_shard_room_bucket_unlink((_DWORD *)j);
        rf_glass_shard_pool_release((_DWORD *)j);
      }
    }
  }
}

