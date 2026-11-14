// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A16D0 rf_server_sync_item_create_to_peer
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(peer,item,raw16 slot). Argument-order adapter to send_item_create_packet45(item,peer,slot); native pushes original third DWORD but target serializes low16. No own
// runtime/authority/state/null checks or allocation. Returns underlying EAX artifact. Called by initial world-state sync for indexed items and unindexed items with slot-1.
int __cdecl rf_server_sync_item_create_to_peer(int a1, int a2, __int16 a3)
{
  return rf_multiplayer_send_item_create_packet45(a2, a1, a3);
}

