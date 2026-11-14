// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049A530 rf_server_sync_entity_spawn_to_peer
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(peer,entity). Thin argument-order adapter: calls already decoded rf_server_send_entity_spawn_to_peer(entity,peer), which builds packet44, then propagates EAX. No own
// mode/authority/null/connection-state filter or allocation. Native two DWORD caller-cleaned stack arguments; world-state synchronization calls this after its entity flag filters.
int __cdecl rf_server_sync_entity_spawn_to_peer(int a1, int a2)
{
  return rf_server_send_entity_spawn_to_peer(a2, a1);
}

