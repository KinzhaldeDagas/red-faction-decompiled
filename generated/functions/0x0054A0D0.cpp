// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054A0D0 rf_world_packet_scratch_reset_bridge
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Recovered no-argument bridge calls54ADA0 shared scratch rewind/owner invalidation,returns its incidental EAX unchanged. Rewinds global packet arena cursor and clears tracked owner+4 pointers/count through callee;does not free arena or clear contents. Not a separate allocator or success predicate.
void *__cdecl rf_world_packet_scratch_reset_bridge()
{
  return rf_scratch_arena_rewind_and_clear_owners();
}

