// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C7050 rf_glass_shard_bucket_render
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl ownerKey. Scans keys, FIRST match only, walks its circular head until next==CURRENT head (NULLempty returns). Calls renderer backend wrapper once per node without own
// budget96,delay108,flags196,active count or lifetime filter. Loads next AFTER renderer callback, not snapshotted before; assumes callback preserves list. Does not register a missing
// key, reclaim settled nodes, mutate bucket counters or own actual backend drawing. EAX incidental key/last-node/index, not reliable rendered count/status.
_DWORD *__cdecl rf_glass_shard_bucket_render(_DWORD *a1)
{
  _DWORD *result; // eax
  _DWORD *v2; // [esp+0h] [ebp-Ch]
  _DWORD *j; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < rf_glass_shard_bucket_count; ++i )
  {
    result = (_DWORD *)rf_glass_shard_bucket_keys[2 * i];
    if ( result == a1 )
    {
      for ( j = (_DWORD *)rf_glass_shard_bucket_heads[2 * i]; j; j = v2 )
      {
        rf_glass_shard_render_backend_wrapper((int)j);
        result = j;
        if ( *j == rf_glass_shard_bucket_heads[2 * i] )
        {
          v2 = nullptr;
        }
        else
        {
          result = j;
          v2 = (_DWORD *)*j;
        }
      }
      return result;
    }
    result = (_DWORD *)(i + 1);
  }
  return result;
}

