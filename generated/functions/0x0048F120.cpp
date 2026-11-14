// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048F120 rf_multiplayer_server_session_tick
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl no arguments; top-level48F000 selects this only mode1/authority1,body has no independent initial admission check. Calls peer prune48F280,accept48F5B0,match-limit
// evaluator48F490 in order. Wrapped deadline704EA8 elapsed OR unarmed broadcasts netgame_update26(peerNULL) then rearms2500ms. Raw game mode accessor492030 must equal1 or2 for deadline704F1C
// unarmed OR elapsed to call494C50(NULL),then rearm5000ms. Other modes leave that timer unchanged.
// Deadline704F20 elapsed OR unarmed traverses all players,skips local and netNULL,calls4A9E40(player) for each remaining,then rearms3500ms even if none. Only predicate446500 nonzero
// calls4A9B10 then4A1ED0. Always finishes4ACE00 then4A04F0,returns latter EAX. No catch-up loop,per-peer timer,clock-delta accumulation or timer rearm on skipped branches.
int rf_multiplayer_server_session_tick()
{
  _DWORD *v1; // [esp+0h] [ebp-Ch]
  _DWORD *i; // [esp+4h] [ebp-8h]
  int v3; // [esp+8h] [ebp-4h]

  rf_multiplayer_server_prune_reliable_peers();
  rf_multiplayer_server_accept_one_reliable_peer();
  sub_48F490();
  if ( rf_clock_deadline_has_elapsed_half_period(&dword_704EA8) || !rf_timestamp_is_armed_nonnegative(&dword_704EA8) )
  {
    rf_multiplayer_send_netgame_update_packet26(0);
    rf_clock_deadline_set_wrapped_offset(&dword_704EA8, 2500);
  }
  v3 = rf_multiplayer_game_mode_get();
  if ( (v3 == 1 || v3 == 2)
    && (!rf_timestamp_is_armed_nonnegative(&dword_704F1C) || rf_clock_deadline_has_elapsed_half_period(&dword_704F1C)) )
  {
    rf_server_send_team_score_packet53(0);
    rf_clock_deadline_set_wrapped_offset(&dword_704F1C, 5000);
  }
  if ( rf_clock_deadline_has_elapsed_half_period(&dword_704F20) || !rf_timestamp_is_armed_nonnegative(&dword_704F20) )
  {
    for ( i = (_DWORD *)dword_87C324; i; i = v1 )
    {
      if ( i != (_DWORD *)rf_local_fpgun_player && i[1152] )
        rf_multiplayer_peer_update_interval_recompute((int)i);
      if ( *i == dword_87C324 )
        v1 = nullptr;
      else
        v1 = (_DWORD *)*i;
    }
    rf_clock_deadline_set_wrapped_offset(&dword_704F20, 3500);
  }
  if ( rf_ui_panel_stack_contains11() )
  {
    rf_multiplayer_queue_entity_updates_to_peers();
    rf_multiplayer_item_active_bitmap_tick();
  }
  rf_powerup_nodes_expire_elapsed();
  return rf_network_flush_all_player_queues();
}

