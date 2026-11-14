// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4CF0 rf_client_send_pong_packet25
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// No arguments. Runtime1/authority EXACT0 builds empty3-byte opcode25,payloadWORD0,and sends directly unreliable to shared server endpoint704EF4. No aggregate queue/stat-recorder
// call,peer lookup,RTT mutation or endpoint validation here. Ping callback24 invokes it. EAX guard/transport/epilogue artifact.
int rf_client_send_pong_packet25()
{
  int result; // eax
  char v1; // [esp+8h] [ebp-208h] BYREF
  __int16 v2; // [esp+9h] [ebp-207h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    v1 = 25;
    v2 = 0;
    return rf_network_send_unreliable((int)&dword_704EF4, &v1, 3u);
  }
  return result;
}

