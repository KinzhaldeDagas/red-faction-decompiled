// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A5550 rf_multiplayer_notify_departure_and_flush
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// No arguments, no runtime/null guard. Authority EXACT1 broadcasts end_game8. Every other authority reads local/net pointer and, only when handle+16!=-1,queues local id/reason1
// left_game7 to local peer. ALWAYS finishes flush_all_player_queues even if no notification queued; returns flush artifact. Called during initialization and teardown; does not itself
// destroy player/state or wait for transport acknowledgement.
_DWORD *rf_multiplayer_notify_departure_and_flush()
{
  if ( rf_multiplayer_server_authority == 1 )
  {
    rf_multiplayer_broadcast_end_game_packet8();
  }
  else if ( *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16) != -1 )
  {
    rf_multiplayer_send_left_game_to_peer_packet7(rf_local_fpgun_player, 1);
  }
  return rf_network_flush_all_player_queues();
}

