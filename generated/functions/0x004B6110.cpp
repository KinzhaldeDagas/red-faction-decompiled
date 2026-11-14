// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B6110 rf_client_send_reload_request_with_200ms_throttle47
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Cdecl raw DWORD. Only runtime1 authority EXACT0. If local player exists require fpgun action0 inactive,action1 inactive,and semantic state2 neither current
// nor pending; any nonzero AL rejects. Local player NULL BYPASSES these fpgun checks, but still reaches queue with NULL. Global deadline7B4DE0: if armed-nonnegative require
// half-period-elapsed nonzero; disarmed admits. On admission arm deadline offset200ms BEFORE constructing/sending opcode47,WORD payload4,total7,raw argumentDWORD at3.
// reliable_queue(localPlayer,packet,7,requireActive0). Timer remains armed regardless send failure; global throttle, not per entity. No weapon/ID validation or current-ammo mutation.
// Receiver reads raw DWORD but chooses actual owner/entity from sender endpoint rather than this word. Nominal char AL residue/delegate, not consistent sent status.
char __cdecl rf_client_send_reload_request_with_200ms_throttle47(int a1)
{
  char result; // al
  unsigned __int8 Src[516]; // [esp+Ch] [ebp-208h] BYREF

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1
    && !rf_multiplayer_server_authority
    && (!rf_local_fpgun_player
     || (result = rf_fpgun_action_is_active(rf_local_fpgun_player, 0)) == 0
     && (result = rf_fpgun_action_is_active(rf_local_fpgun_player, 1u)) == 0
     && (result = rf_fpgun_state_is_resident(rf_local_fpgun_player, 2)) == 0)
    && (!rf_timestamp_is_armed_nonnegative(&dword_7B4DE0)
     || (result = rf_clock_deadline_has_elapsed_half_period(&dword_7B4DE0)) != 0) )
  {
    rf_clock_deadline_set_wrapped_offset(&dword_7B4DE0, 200);
    Src[0] = 47;
    *(_DWORD *)&Src[3] = a1;
    *(_WORD *)&Src[1] = 4;
    return rf_multiplayer_queue_reliable_packet(rf_local_fpgun_player, Src, 7u, 0);
  }
  return result;
}

