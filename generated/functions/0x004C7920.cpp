// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C7920 rf_glass_shard_pool_release
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl shard. Unconditionally decrements signed active count, appends node at FREE circular tail if free head nonnull, otherwise self-links and installshead. Returns shard pointer.
// Does NOT unlink from owner bucket, clear owner104, validate active membership/null/double release, zero timers/velocity/flags/payload or free memory/bitmap. Caller must separately
// unlink; normal settling does NOT call release and persists in renderer. Invalid calls corrupt count/list; all XOR/JNZ tails dead.
_DWORD *__cdecl rf_glass_shard_pool_release(_DWORD *a1)
{
  --rf_glass_shard_active_count;
  if ( rf_glass_shard_free_head )
  {
    a1[1] = *(_DWORD *)(rf_glass_shard_free_head + 4);
    *a1 = rf_glass_shard_free_head;
    **(_DWORD **)(rf_glass_shard_free_head + 4) = a1;
    *(_DWORD *)(rf_glass_shard_free_head + 4) = a1;
    return a1;
  }
  else
  {
    *a1 = a1;
    a1[1] = a1;
    rf_glass_shard_free_head = a1;
    return a1;
  }
}

