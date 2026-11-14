// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C6ED0 rf_glass_shard_room_bucket_link
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl shard,owner key from104. Scans signed i<bucketCount,first exact match. Existing nonempty: append shard before head using tail=head.prev4, keep head,returns OLD head pointer.
// Existing empty head: links self/self,head=shard,returns shard. No match: writes key at bucketCount and clears head, self-links shard and sets newhead, increments bucketCount,
// returns NEW COUNT cast to pointer. Return is not uniform node/status.
// Registry initialized for64 stride8 key/head slots but NO capacity guard, vacant-key reuse/compaction or count decrement. Empty bucket retains key and is reused only by SAME owner.
// OwnerNULL allowed, duplicate/node-membership/unlinked-state not checked. New-key count may grow beyond64; zeroed-newhead makes nominal nonempty-newbucket branch dead in ordinary
// nonaliasing state. Does not increment active shard count, allocate or initialize payload; caller owns those.
_DWORD *__cdecl rf_glass_shard_room_bucket_link(_DWORD *a1)
{
  _DWORD *result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_glass_shard_bucket_count; ++i )
  {
    if ( rf_glass_shard_bucket_keys[2 * i] == a1[26] )
    {
      if ( rf_glass_shard_bucket_heads[2 * i] )
      {
        a1[1] = *(_DWORD *)(rf_glass_shard_bucket_heads[2 * i] + 4);
        *a1 = rf_glass_shard_bucket_heads[2 * i];
        **(_DWORD **)(rf_glass_shard_bucket_heads[2 * i] + 4) = a1;
        result = (_DWORD *)rf_glass_shard_bucket_heads[2 * i];
        result[1] = a1;
      }
      else
      {
        *a1 = a1;
        a1[1] = a1;
        rf_glass_shard_bucket_heads[2 * i] = (int)a1;
        return a1;
      }
      return result;
    }
  }
  rf_glass_shard_bucket_keys[2 * rf_glass_shard_bucket_count] = a1[26];
  rf_glass_shard_bucket_heads[2 * rf_glass_shard_bucket_count] = 0;
  if ( rf_glass_shard_bucket_heads[2 * rf_glass_shard_bucket_count] )
  {
    a1[1] = *(_DWORD *)(rf_glass_shard_bucket_heads[2 * rf_glass_shard_bucket_count] + 4);
    *a1 = rf_glass_shard_bucket_heads[2 * rf_glass_shard_bucket_count];
    **(_DWORD **)(rf_glass_shard_bucket_heads[2 * rf_glass_shard_bucket_count] + 4) = a1;
    *(_DWORD *)(rf_glass_shard_bucket_heads[2 * rf_glass_shard_bucket_count] + 4) = a1;
  }
  else
  {
    *a1 = a1;
    a1[1] = a1;
    rf_glass_shard_bucket_heads[2 * rf_glass_shard_bucket_count] = (int)a1;
  }
  return (_DWORD *)++rf_glass_shard_bucket_count;
}

