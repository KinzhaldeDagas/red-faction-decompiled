// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BFC80 rf_collision_pair_pool_initialize8192
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): No arguments. Iterates i0..8191, prepending each16-byte record from base7F3BD0+16*i to free-list header813C18 through count-incrementing push. Does NOT clear free/active headers or pair payload fields first. If initially empty, final free head is record8191 and count8192; repeated initialization can corrupt reused links/counts. Registers no-op shutdown4BFCD0 with atexit and returns atexit result. No heap allocation, active-pair destruction or automatic payload/reference cleanup.
int rf_collision_pair_pool_initialize8192()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 0x2000; ++i )
    rf_intrusive_slist_push_front(dword_813C18, &dword_7F3BD0[4 * i]);
  return atexit(rf_collision_pair_pool_shutdown_hook_noop);
}

