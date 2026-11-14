// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B07B0 rf_client_send_in_game_packet11
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Noarg. Unguarded local/net read of netID BYTE20, construct opcode11,WORD payload1,total4 bytes. Reliable_queue(localPlayer,packet,4,requireActive0),
// return queue EAX. No runtime/authority/connection-state admission, peer-ready mutation or timer update.
int rf_client_send_in_game_packet11()
{
  unsigned __int8 Src; // [esp+Ch] [ebp-208h] BYREF
  __int16 v2; // [esp+Dh] [ebp-207h]
  char v3; // [esp+Fh] [ebp-205h]

  Src = 11;
  v3 = *(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20);
  v2 = 1;
  return rf_multiplayer_queue_reliable_packet(rf_local_fpgun_player, &Src, 4u, 0);
}

