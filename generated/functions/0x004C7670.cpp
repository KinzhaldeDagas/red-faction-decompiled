// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C7670 rf_glass_resting_shard_overlap_test
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, full rectangular/general quad tessellation, ordered edge selection and stale loop indices, native UV/grid coordinates, pool freshness and delayed launch semantics): 
// Cdecl common query object ->ALbool. For each bucket whose key equals query DWORD0 cached room:
// R2=F32(radius120^2),upper=F32(queryY64-radius120+DOUBLE.009999999776482582),lower=F32(queryY64-radius120-DOUBLE.009999999776482582). For each shard budget96<=0: native vertical
// predicate is (lower<=shardY12 OR unordered) OR (upper>=shardY12 OR unordered), NOT a feet-height band conjunction. For ordinary finite lower<=upper this OR admits EVERY shard Y, so
// actual spatial restriction is following STRICT ORDERED R2>distanceSquared(shard.center8,query.commonPosition60). Equality/NaN distance/radius rejects. Returns1 on first admitted
// resting shard else0; negative radius still squared. No flags/attachment/liquid/health/player-type/visibility test, radius of shard not added, no mutation or NULL query guard.
char __cdecl rf_glass_resting_shard_overlap_test(float *a1)
{
  int v2; // [esp+0h] [ebp-18h]
  float v3; // [esp+4h] [ebp-14h]
  float v4; // [esp+8h] [ebp-10h]
  float v5; // [esp+Ch] [ebp-Ch]
  int j; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  for ( i = 0; i < rf_glass_shard_bucket_count; ++i )
  {
    if ( rf_receiver_get_first_dword(a1) == rf_glass_shard_bucket_keys[2 * i] )
    {
      v4 = a1[30] * a1[30];
      v5 = a1[16] - a1[30] + 0.009999999776482582;
      v3 = a1[16] - a1[30] - 0.009999999776482582;
      for ( j = rf_glass_shard_bucket_heads[2 * i]; j; j = v2 )
      {
        if ( *(int *)(j + 96) <= 0
          && (v3 <= (double)*(float *)(j + 12) || v5 >= (double)*(float *)(j + 12))
          && v4 > rf_vector_distance_squared((const float *)(j + 8), a1 + 15) )
        {
          return 1;
        }
        if ( *(_DWORD *)j == rf_glass_shard_bucket_heads[2 * i] )
          v2 = 0;
        else
          v2 = *(_DWORD *)j;
      }
    }
  }
  return 0;
}

