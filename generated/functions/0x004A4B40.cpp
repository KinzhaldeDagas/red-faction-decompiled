// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A4B40 rf_multiplayer_broadcast_end_game_packet8
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// No arguments. Fixed3-byte opcode8,end_game,payload0; common reliable fanout(buffer,3,0). No own runtime/authority/state guard, teardown or immediate flush. shutdown notifier5550
// calls it for authority exactly1. EAX incidental.
int rf_multiplayer_broadcast_end_game_packet8()
{
  unsigned __int8 Src; // [esp+8h] [ebp-208h] BYREF
  __int16 v2; // [esp+9h] [ebp-207h]

  Src = 8;
  v2 = 0;
  return rf_server_broadcast_packet(&Src, 3, 0);
}

