// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C85A0 rf_glass_shard_pool_allocate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, full rectangular/general quad tessellation, ordered edge selection and stale loop indices, native UV/grid coordinates, pool freshness and delayed launch semantics): 
// Cdecl(outShardPointer,requestedOwner), AL is FRESH-vs-RECYCLED, not success. Signed activeCount<384: increments count,pops first free node (singleton clears free head; multi
// advances head),unlinks/clears links,AL1. Otherwise count unchanged: scans bucket keys in index order,remembers LAST matching requested-owner index,chooses HEAD of FIRST nonmatching
// NONEMPTY bucket and stops. If none and matching index exists chooses its head WITHOUT empty check. Removes selected node from its circular bucket,retains key/count,AL0. No
// oldest-global/time/visibility/distance/resting preference.
// Always selectedNode.room104=0,*out=selectedNode,return freshness BYTE. Preserves all other payload/timers/material/attachment flags. Does NOT append bucket/free list or initialize
// node. Assumes count/free/bucket invariants: count<384 with freeNULL dereferencesNULL; full pool with no eligible/matching bucket reaches selectedNULL write; matching empty bucket
// dereferencesNULL. No clean NULL failure return despite callers testing out pointer. No heap allocation, operator delete, bitmap release or rollback of counter on invalid state.
// RecycledAL0 is ordinary usable output and must not be treated as failure.
char __cdecl rf_glass_shard_pool_allocate(_DWORD *a1, int a2)
{
  char v3; // [esp+3h] [ebp-11h]
  int v4; // [esp+4h] [ebp-10h]
  _DWORD *v5; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]
  char v7; // [esp+13h] [ebp-1h]

  v5 = nullptr;
  if ( rf_glass_shard_active_count < 384 )
  {
    ++rf_glass_shard_active_count;
    v5 = rf_glass_shard_free_head;
    if ( (_DWORD *)*rf_glass_shard_free_head == rf_glass_shard_free_head )
    {
      *rf_glass_shard_free_head = 0;
      v5[1] = 0;
      rf_glass_shard_free_head = nullptr;
    }
    else
    {
      rf_glass_shard_free_head = (_DWORD *)*rf_glass_shard_free_head;
      *(_DWORD *)v5[1] = *v5;
      *(_DWORD *)(*v5 + 4) = v5[1];
      *v5 = 0;
      v5[1] = 0;
    }
    v7 = 1;
  }
  else
  {
    v3 = 0;
    v4 = -1;
    for ( i = 0; i < rf_glass_shard_bucket_count; ++i )
    {
      if ( rf_glass_shard_bucket_keys[2 * i] == a2 )
      {
        v4 = i;
      }
      else
      {
        v5 = (_DWORD *)rf_glass_shard_bucket_heads[2 * i];
        if ( v5 )
        {
          if ( (_DWORD *)*v5 == v5 )
          {
            *v5 = 0;
            v5[1] = 0;
            rf_glass_shard_bucket_heads[2 * i] = 0;
          }
          else
          {
            rf_glass_shard_bucket_heads[2 * i] = *v5;
            *(_DWORD *)v5[1] = *v5;
            *(_DWORD *)(*v5 + 4) = v5[1];
            *v5 = 0;
            v5[1] = 0;
          }
          v7 = 0;
          v3 = 1;
          break;
        }
      }
    }
    if ( !v3 && v4 != -1 )
    {
      v5 = (_DWORD *)rf_glass_shard_bucket_heads[2 * v4];
      if ( (_DWORD *)*v5 == v5 )
      {
        *v5 = 0;
        v5[1] = 0;
        rf_glass_shard_bucket_heads[2 * v4] = 0;
      }
      else
      {
        rf_glass_shard_bucket_heads[2 * v4] = *v5;
        *(_DWORD *)v5[1] = *v5;
        *(_DWORD *)(*v5 + 4) = v5[1];
        *v5 = 0;
        v5[1] = 0;
      }
      v7 = 0;
    }
  }
  v5[26] = 0;
  *a1 = v5;
  return v7;
}

