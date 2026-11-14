// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A41B0 rf_multiplayer_send_browser_query_packet0
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(endpoint). Builds empty opcode0 (3-byte header,payload WORD0) and directly sends unreliable to endpoint. No own runtime/authority/endpoint-null guard, peer lookup or retry
// timer. Unlike LAN query wrapper this routine does not construct a broadcast address. EAX is transport/epilogue artifact.
int __cdecl rf_multiplayer_send_browser_query_packet0(int a1)
{
  char v2; // [esp+8h] [ebp-208h] BYREF
  __int16 v3; // [esp+9h] [ebp-207h]

  v2 = 0;
  v3 = 0;
  return rf_network_send_unreliable(a1, &v2, 3u);
}

