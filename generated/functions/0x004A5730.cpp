// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A5730 rf_multiplayer_broadcast_enter_limbo_packet21
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// No arguments. Fixed3-byte opcode21 enter_limbo,payload0; common reliable fanout(require-active0). No own runtime/authority guard or UI/state mutation. Existing match-transition
// caller5600 supplies policy; sender does not flush.
int rf_multiplayer_broadcast_enter_limbo_packet21()
{
  unsigned __int8 Src; // [esp+8h] [ebp-208h] BYREF
  __int16 v2; // [esp+9h] [ebp-207h]

  Src = 21;
  v2 = 0;
  return rf_server_broadcast_packet(&Src, 3, 0);
}

