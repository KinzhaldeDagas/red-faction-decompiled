// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048F6E0 rf_multiplayer_client_check_reliable_connection
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl no arguments. Dereferences local player and net4608 withoutNULL guard. Peer net16==-1 skips check. Other handles queried; state EXACT0,2 or3 calls
// multiplayer_runtime_teardown with NO native pushed arguments,then requests immediate panel(13,1),returning request result. Other state retained. Does not run pending5-second
// timeout,close a peer directly,or test startup/mode/authority bytes itself. Return register incidental outside panel-request path.
int rf_multiplayer_client_check_reliable_connection()
{
  int result; // eax

  result = rf_local_fpgun_player;
  if ( *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16) != -1 )
  {
    result = rf_reliable_udp_get_peer_state(*(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16));
    if ( result == 2 || result == 3 || !result )
    {
      rf_multiplayer_runtime_teardown();
      return rf_ui_request_panel_immediate(13, 1);
    }
  }
  return result;
}

