// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B0670 rf_client_state_sync_update_and_check_timeout
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Noarg. Unguarded local player/net. If net state12==0 call state-info-request9 sender then write state1 regardless queue result; no retry while state1.
// Independently if state12==2 AND pending GeoMod queue count==0: choose respawn position/matrix, write view wrapper through411910/411950, invoke4122A0, request panel11 unforced.
// Queue count excludes currently executing operation, so this check is not proof all terrain work finished; no active-operation-phase test here. No state3/once-only latch on this
// branch; can repeat when panel refused/still called. ALWAYS afterwards query shared timer7B25EC. Only result AL EXACT1 calls client_leave_game_notify_and_exit(local netID,reason6);
// can do so AFTER same-call view/panel11 request. Delegate has its own client/runtime checks. No own runtime/authority/local/net guards, timeout reset on completion, send-error
// handling or completion return; nominal char AL residue/delegate.
char rf_client_state_sync_update_and_check_timeout()
{
  char result; // al
  float v1[3]; // [esp+0h] [ebp-30h] BYREF
  float v2[9]; // [esp+Ch] [ebp-24h] BYREF

  if ( !*(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 12) )
  {
    rf_client_send_state_info_request_packet9();
    *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 12) = 1;
  }
  if ( *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 12) == 2 && !rf_geomod_execution_queue_count_get() )
  {
    rf_vector3_default_construct_noop(v1);
    rf_matrix3_construct((char *)v2);
    rf_respawn_point_select(v1, v2, rf_local_fpgun_player);
    rf_camera_slot_copy_position_and_vectorE4(*(_DWORD *)(rf_local_fpgun_player + 196), v1);
    sub_411950(*(_DWORD *)(rf_local_fpgun_player + 196), v2);
    rf_camera_slot_advance_sample_and_set_state6(*(_DWORD *)(rf_local_fpgun_player + 196));
    rf_ui_request_panel_immediate(11, 0);
  }
  result = rf_replicator_has_elapsed(&unk_7B25EC);
  if ( result == 1 )
    return rf_client_leave_game_notify_and_exit(*(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20), 6);
  return result;
}

