// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A09E0 rf_server_broadcast_object_respawn_packet_43
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(raw object UID). No own runtime/authority/object-existence guard. Builds fixed7-byte opcode43: payload WORD1=4 and one raw DWORD UID at3, then common reliable
// fanout(buffer,7,0). No static incoming code/data xrefs currently; live invocation is not established. Does not translate UID, allocate a player/entity, reactivate an object
// directly or include player-spawn presentation. EAX is transport/epilogue artifact; existing descriptive name/comments retained.
int __cdecl rf_server_broadcast_object_respawn_packet_43(int a1)
{
  unsigned __int8 v2[516]; // [esp+Ch] [ebp-208h] BYREF

  v2[0] = 43;
  *(_DWORD *)&v2[3] = a1;
  *(_WORD *)&v2[1] = 4;
  return rf_server_broadcast_packet(v2, 7, 0);
}

