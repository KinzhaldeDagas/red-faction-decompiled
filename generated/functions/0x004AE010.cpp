// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AE010 rf_client_send_respawn_request
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout):
// Cdecl(characterSelection DWORD,networkID lowBYTE). Unconditionally build opcode14,WORD payload5,total8 bytes: selection bytes3..6,playerID byte7. No team byte, validation,
// runtime/authority/local-player guard or reliable transport. Call unreliable_player_queue(current local player,packet,8) and preserve delegate EAX; invalid character selections are
// transmitted raw. Existing respawn wire description confirmed from native DWORD/BYTE stores.
int __cdecl rf_client_send_respawn_request(int a1, char a2)
{
  char Src[516]; // [esp+10h] [ebp-208h] BYREF

  Src[0] = 14;
  *(_DWORD *)&Src[3] = a1;
  Src[7] = a2;
  *(_WORD *)&Src[1] = 5;
  return rf_network_queue_unreliable_player_packet(rf_local_fpgun_player, Src, 8);
}

