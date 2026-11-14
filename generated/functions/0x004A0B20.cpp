// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A0B20 rf_multiplayer_broadcast_item_create_packet45
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Recovered original [4A0B20,4A0B37), cdecl(item,slot). Thin wrapper to send_item_create_packet45(item,NULL,slot), forwards raw argument DWORD (callee serializes low16) and
// propagates EAX. No own mode/authority/validation/state mutation; no static incoming xrefs currently. NULL peer selects common reliable fanout.
int __cdecl rf_multiplayer_broadcast_item_create_packet45(int item, int slot)
{
  return rf_multiplayer_send_item_create_packet45(item, 0, slot);
}

