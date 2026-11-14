// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A04D0 rf_network_flush_player_queues
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(player). Calls player unreliable flush FIRST and reliable flush SECOND with the same pointer, then propagates second callee EAX. No own runtime/authority/null/state guard.
// Does not stop after first transport failure; both delegates ignore transport result and clear positive-length queues after attempted sends.
int __cdecl rf_network_flush_player_queues(int a1)
{
  rf_network_flush_player_unreliable_queue(a1);
  return rf_network_flush_player_reliable_queue(a1);
}

