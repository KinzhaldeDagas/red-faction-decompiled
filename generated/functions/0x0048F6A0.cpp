// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048F6A0 rf_multiplayer_client_session_tick
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl no arguments. Calls client connection-check48F6E0 and IGNORES its result; even if that delegate tears down runtime,continues to predicate446500. When predicate
// true,calls490180,then if global local-entity681E38 nonnull calls4A99E0. Always calls4A04D0(current local player pointer) and returns its EAX. No early return after
// disconnect,independent runtime-mode/authority guard or null-pointer repair.
int rf_multiplayer_client_session_tick()
{
  rf_multiplayer_client_check_reliable_connection();
  if ( rf_ui_panel_stack_contains11() )
  {
    rf_multiplayer_client_timeout_warning_update();
    if ( dword_681E38 )
      rf_multiplayer_client_queue_entity_update_packet38();
  }
  return rf_network_flush_player_queues(rf_local_fpgun_player);
}

