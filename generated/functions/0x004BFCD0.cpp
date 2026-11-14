// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BFCD0 rf_collision_pair_pool_shutdown_hook_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Exact55 8B EC 5D C3; atexit hook from pair-pool initialization. No traversal, reset, object/pair/resource free or application writes; preserves incoming EAX with no defined return.
void __cdecl rf_collision_pair_pool_shutdown_hook_noop()
{
  ;
}

