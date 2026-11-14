// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C5EB0 rf_glass_register_empty_exit_hook
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl no args, atexit(4C5ED0), returns registration EAX. Does not allocate/init/free shards, texture, bucket storage or sound voices; registered callback is verified empty.
int rf_glass_register_empty_exit_hook()
{
  return atexit(sub_4C5ED0);
}

