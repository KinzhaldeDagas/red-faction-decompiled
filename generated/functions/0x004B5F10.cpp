// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B5F10 rf_client_send_select_weapon_request_packet28
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Recovered4B5F10..4B5FF5,lastRET4B5FF4. Cdecl raw weaponDWORD. Only runtime1 authority EXACT0 build opcode28,WORD payload4,total7,weapon at3..6.
// reliable_queue(localPlayer,packet,7,requireActive0). No local-player/weapon-range/ownership guard or selected-weapon mutation in sender. Native no meaningful return; server
// receiver binds ownership using source endpoint.
void __cdecl rf_client_send_select_weapon_request_packet28(int weapon)
{
  unsigned __int8 v1[516]; // [esp+Ch] [ebp-208h] BYREF

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    v1[0] = 28;
    *(_DWORD *)&v1[3] = weapon;
    *(_WORD *)&v1[1] = 4;
    rf_multiplayer_queue_reliable_packet(rf_local_fpgun_player, v1, 7u, 0);
  }
}

