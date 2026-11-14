// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A4D30 rf_multiplayer_send_left_game_to_peer_packet7
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(peer,raw reason BYTE). Fixed5-byte opcode7,payload2; idBYTE3 from peer net+4608+20,reasonBYTE4 from low argument byte. Queues reliable to SAME peer(require-active0). No own
// peer/net/runtime/authority/state validation. Caller5550 uses local peer to notify server; queue helper can substitute local in client mode. No direct removal/flush.
int __cdecl rf_multiplayer_send_left_game_to_peer_packet7(int a1, char a2)
{
  unsigned __int8 Src; // [esp+Ch] [ebp-208h] BYREF
  __int16 v4; // [esp+Dh] [ebp-207h]
  char v5; // [esp+Fh] [ebp-205h]
  char v6; // [esp+10h] [ebp-204h]

  Src = 7;
  v5 = *(_BYTE *)(*(_DWORD *)(a1 + 4608) + 20);
  v6 = a2;
  v4 = 2;
  return rf_multiplayer_queue_reliable_packet(a1, &Src, 5u, 0);
}

