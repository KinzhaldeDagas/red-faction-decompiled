// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C6DE0 rf_glass_shard_move_bucket
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl(shard,newOwner). Scans keys to first==old room104. If node is head+singleton,headNULL and links0/4 cleared; head+multi advanceshead to next then unlinks; nonhead unlinks
// using prev/next unchecked. Clears room104 on matching removal, preserves bucket KEY/count even empty. If no key matches, old links/owner are NOT cleared before continuation. Always
// writes newOwner104 then calls link6ED0, forwarding incidental EAX. Thus missing old key can leave existing list damaged by relink; no membership check/NULL/same-owner shortcut,
// payload reset, active-count change or node allocation/free.
int __cdecl rf_glass_shard_move_bucket(_DWORD *a1, int a2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_glass_shard_bucket_count; ++i )
  {
    if ( rf_glass_shard_bucket_keys[2 * i] == a1[26] )
    {
      if ( (_DWORD *)rf_glass_shard_bucket_heads[2 * i] == a1 )
      {
        if ( (_DWORD *)*a1 == a1 )
        {
          *a1 = 0;
          a1[1] = 0;
          rf_glass_shard_bucket_heads[2 * i] = 0;
LABEL_9:
          a1[26] = 0;
          break;
        }
        rf_glass_shard_bucket_heads[2 * i] = *a1;
      }
      *(_DWORD *)a1[1] = *a1;
      *(_DWORD *)(*a1 + 4) = a1[1];
      *a1 = 0;
      a1[1] = 0;
      goto LABEL_9;
    }
  }
  a1[26] = a2;
  return rf_glass_shard_room_bucket_link(a1);
}

