// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049ABB0 rf_client_send_suicide_packet20
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Noarg. Only runtime1 authority EXACT0 build opcode20,WORD payload0,total3; queue_unreliable_player_packet(localPlayer,packet,3), return delegate/incidental
// EAX. No local-player NULL, alive/entity ownership or rate-limit checks here. No playerID or damage value transmitted; receiver selects player by source endpoint.
int rf_client_send_suicide_packet20()
{
  int result; // eax
  char Src; // [esp+8h] [ebp-208h] BYREF
  __int16 v2; // [esp+9h] [ebp-207h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    Src = 20;
    v2 = 0;
    return rf_network_queue_unreliable_player_packet(rf_local_fpgun_player, &Src, 3);
  }
  return result;
}

