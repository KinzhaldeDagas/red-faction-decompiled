// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A5590 rf_server_kick_and_remove_player
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(player). Runtime1/authority1 and nonnull player required, but NO local-player exclusion/net-null guard. Game mode EXACT1 invokes CTF drop helper, then always removes flag
// nodes4AD410,broadcasts id from net+20 with reason2,delegates remove_player_and_mark_object,in that order. Does not wait for successful broadcast/flush or append banlist itself.
// Admin/prune callers separately filter local. EAX guard/delegate artifact.
int __cdecl rf_server_kick_and_remove_player(int a1)
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 && a1 )
  {
    if ( rf_multiplayer_game_mode_get() == 1 )
      rf_ctf_drop_player_carried_flag(a1);
    rf_network_remove_player_flag_nodes(a1);
    rf_multiplayer_broadcast_left_game_packet7(*(_BYTE *)(*(_DWORD *)(a1 + 4608) + 20), 2);
    return rf_multiplayer_remove_player_and_mark_object(a1);
  }
  return result;
}

