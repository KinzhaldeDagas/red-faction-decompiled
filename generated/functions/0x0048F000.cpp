// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048F000 rf_multiplayer_session_tick_if_enabled
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Native no-stack-argument entry; saved prototype void(). ANY nonzero startup/session BYTE704E80 runs4B1CC0 then49FD20. Only runtime mode EXACT1 AND authority EXACT1 chooses server
// tick48F120; EVERY other mode/authority combination chooses client tick48F6A0. Then remote statistics48F050 and4A6420 run in that order. Zero session flag returns without helper
// calls. No own mode/authority initialization or networking-stateNULL guard. Native makes no x87 operations or stack argument setup to4A6420; transitive inferred ST0 usercall
// parameter was not adopted as a verified interface.
void rf_multiplayer_session_tick_if_enabled()
{
  if ( rf_startup_session_flag )
  {
    rf_tracker_update_send_retries_and_process_one_reply();
    rf_multiplayer_receive_and_dispatch_queued_packets();
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      rf_multiplayer_server_session_tick();
    else
      rf_multiplayer_client_session_tick();
    rf_multiplayer_remote_statistics_update();
    rf_multiplayer_log_uptime_tick();
  }
}

