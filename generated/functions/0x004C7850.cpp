// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C7850 rf_glass_shard_room_bucket_unlink
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl shard. Scans bucket keys for shard.room104, FIRST match. Head singleton ->links0/4=NULL,headNULL; head multi ->head=next then normal prev/next unlink; nonhead uses supplied
// links unchecked. Clears shard.room104 ONLY when key matched, leaves bucket key/count forever. Missing key leaves node links/owner unchanged. No free-list insertion, active-count
// decrement, payload reset or allocation/free; pool_release separate. Membership/double-unlink not guarded; EAX incidental shard/index/incoming value, not reliable status.
_DWORD *__cdecl rf_glass_shard_room_bucket_unlink(_DWORD *a1)
{
  _DWORD *result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_glass_shard_bucket_count; ++i )
  {
    if ( rf_glass_shard_bucket_keys[2 * i] == a1[26] )
    {
      if ( (_DWORD *)rf_glass_shard_bucket_heads[2 * i] == a1 )
      {
        if ( (_DWORD *)*a1 == a1 )
        {
          result = a1;
          *a1 = 0;
          a1[1] = 0;
          rf_glass_shard_bucket_heads[2 * i] = 0;
LABEL_9:
          a1[26] = 0;
          return result;
        }
        rf_glass_shard_bucket_heads[2 * i] = *a1;
      }
      *(_DWORD *)a1[1] = *a1;
      *(_DWORD *)(*a1 + 4) = a1[1];
      *a1 = 0;
      result = a1;
      a1[1] = 0;
      goto LABEL_9;
    }
    result = (_DWORD *)(i + 1);
  }
  return result;
}

