// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00464FC0 rf_browser_update_queries_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Cdecl suppressInput LOWBYTE. Only suppress0 AND active6F52CA:poll_dispatch(keyhandler465670,0) TWO native args;pointer4632D0 updates all controls,then focused virtual+4
// ECX/no args,mirror indicatorBYTE6F5D30=6F57BC. Tracker/query processing continues regardless input/active gates. TrackerActive:zero100-byte local/ping-1;pop positive
// endpoints,allocate reportedTotal+512 if primaryNULL,import;any negative terminal clears trackerActive,reinserts favorites,only-2 shows no-results/partial error,then queues all
// queries;0 leaves tracker running. Clear busy6F51A0,capture millisecond clock once. Each queued40000000 row when shared5334 disarmed/elapsed:CLEAR queued BEFORE cancel;if
// cancel0,set awaiting20000000,increment wrapping retryBYTE100,timestamp96=now,ping94=-1,send packet0(endpoint84),flush ALL unreliable queues,set busy,arm5334 LAN0ms/online50ms.
// Otherwise awaiting rows:SIGNED32(now-timestamp)>5000 and zero-extended retry>=2 ->completed++,failed++,clear awaiting,single-queryBYTE0;nonnegative nextcursor selects valid raw
// index to queue,then increments cursor/end-1 WITHOUT resetting retry. Fewer attempts ->clear awaiting/requeue. Await branch sets busy if cancel0 even after final timeout clears
// awaiting. Cancel still consumes queued flags without send and processes timeouts/advances cursor;does not stop all internal state. UI busy=tracker/busy/pendingIP/unelapsed
// hold57DC/join537C:Cancel state9=1,Get/Add/RefreshAll/Selected0;Join separately enabled iff no pendingIP and join deadline elapsed. Idle reverses these states. Dirty6F52D9 rebuilds
// indices,optional follow6F52DA ensures selected visible4655D0,then clears both. Always call draw465AC0. No raw query-array/cursor-capacity bounds,send-result rollback or active gate
// around network progression.
int __cdecl rf_browser_update_queries_and_draw(char a1)
{
  _DWORD *v1; // eax
  bool v3; // [esp+0h] [ebp-94h]
  int v4; // [esp+18h] [ebp-7Ch] BYREF
  _WORD v5[52]; // [esp+1Ch] [ebp-78h] BYREF
  int i; // [esp+88h] [ebp-Ch]
  int v7; // [esp+8Ch] [ebp-8h]
  int j; // [esp+90h] [ebp-4h]

  if ( !a1 && unk_6F52CA )
  {
    rf_ui_poll_and_dispatch_event(rf_browser_handle_key);
    rf_browser_update_pointer();
    v1 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, unk_6F519C);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v1 + 4))(*v1);
    unk_6F5D30 = unk_6F57BC;
  }
  if ( unk_6F51A2 )
  {
    memset(v5, 0, 0x64u);
    v5[47] = -1;
    for ( i = rf_tracker_pop_endpoint_and_status((int)v5, &v4); i > 0; i = rf_tracker_pop_endpoint_and_status(
                                                                             (int)v5,
                                                                             &v4) )
    {
      if ( !dword_6F52CC )
      {
        dword_6F5198 = v4 + 512;
        rf_browser_allocate_record_and_index_arrays_once(v4 + 512);
      }
      rf_browser_import_cache100((int)v5, 0);
    }
    if ( i < 0 )
    {
      unk_6F51A2 = 0;
      rf_browser_reinsert_favorite_endpoints();
      if ( i == -2 )
      {
        if ( dword_6F51A8 <= 0 )
          rf_ui_show_ok_modal(unk_88E258, unk_88E260, 0, 0);
        else
          rf_ui_show_ok_modal(unk_88E258, unk_88E25C, 0, 0);
      }
      rf_browser_queue_all_server_queries();
    }
  }
  unk_6F51A0 = 0;
  v7 = rf_performance_clock_elapsed_scaled(1000);
  for ( j = 0; j < dword_6F51A8; ++j )
  {
    if ( (*((_DWORD *)dword_6F52CC + 27 * j + 26) & 0x40000000) != 0
      && (!rf_timestamp_is_armed_nonnegative(&dword_6F5334) || rf_clock_deadline_has_elapsed_half_period(&dword_6F5334)) )
    {
      *((_DWORD *)dword_6F52CC + 27 * j + 26) &= ~0x40000000u;
      if ( !unk_6F51A1 )
      {
        *((_DWORD *)dword_6F52CC + 27 * j + 26) |= 0x20000000u;
        ++*((_BYTE *)dword_6F52CC + 108 * j + 100);
        *((_DWORD *)dword_6F52CC + 27 * j + 24) = v7;
        *((_WORD *)dword_6F52CC + 54 * j + 47) = -1;
        rf_multiplayer_send_browser_query_packet0((int)dword_6F52CC + 108 * j + 84);
        rf_network_flush_all_unreliable_queues();
        unk_6F51A0 = 1;
        if ( byte_6F5DB8[0] )
          rf_clock_deadline_set_wrapped_offset(&dword_6F5334, 0);
        else
          rf_clock_deadline_set_wrapped_offset(&dword_6F5334, 50);
      }
    }
    else if ( (*((_DWORD *)dword_6F52CC + 27 * j + 26) & 0x20000000) != 0 )
    {
      if ( v7 - *((_DWORD *)dword_6F52CC + 27 * j + 24) > 5000 )
      {
        if ( *((unsigned __int8 *)dword_6F52CC + 108 * j + 100) >= 2u )
        {
          ++unk_6F5190;
          ++unk_6F52C0;
          *((_DWORD *)dword_6F52CC + 27 * j + 26) &= ~0x20000000u;
          unk_6F52D8 = 0;
          if ( dword_6F51B0 >= 0 )
          {
            if ( *(int *)(unk_6F52D0 + 4 * dword_6F51B0) >= 0
              && *(_DWORD *)(unk_6F52D0 + 4 * dword_6F51B0) < dword_6F51A8 )
            {
              *((_DWORD *)dword_6F52CC + 27 * *(_DWORD *)(unk_6F52D0 + 4 * dword_6F51B0) + 26) |= 0x40000000u;
            }
            if ( ++dword_6F51B0 >= dword_6F51A8 )
              dword_6F51B0 = -1;
          }
        }
        else
        {
          *((_DWORD *)dword_6F52CC + 27 * j + 26) &= ~0x20000000u;
          *((_DWORD *)dword_6F52CC + 27 * j + 26) |= 0x40000000u;
        }
      }
      if ( !unk_6F51A1 )
        unk_6F51A0 = 1;
    }
  }
  if ( unk_6F51A2
    || unk_6F51A0
    || rf_join_pending_ipv4_is_set()
    || !rf_clock_deadline_has_elapsed_half_period(&dword_6F57DC)
    || !rf_clock_deadline_has_elapsed_half_period(&dword_6F537C) )
  {
    rf_ui_control_set_state_byte9(&dword_6F5770);
    rf_ui_control_clear_state_byte9(&dword_6F5998);
    rf_ui_control_clear_state_byte9(&dword_6F5DC0);
    rf_ui_control_clear_state_byte9(&dword_6F5380);
    rf_ui_control_clear_state_byte9(&dword_6F5B00);
    v3 = !rf_join_pending_ipv4_is_set() && rf_clock_deadline_has_elapsed_half_period(&dword_6F537C);
    unk_6F55B1 = v3;
  }
  else
  {
    rf_ui_control_clear_state_byte9(&dword_6F5770);
    rf_ui_control_set_state_byte9(&dword_6F5998);
    rf_ui_control_set_state_byte9(&dword_6F5DC0);
    rf_ui_control_set_state_byte9(&dword_6F5380);
    rf_ui_control_set_state_byte9(&dword_6F5B00);
    rf_ui_control_set_state_byte9(&dword_6F55A8);
  }
  if ( unk_6F52D9 )
  {
    rf_browser_rebuild_filtered_sorted_row_indices();
    if ( unk_6F52DA )
      rf_browser_ensure_selected_row_visible();
    unk_6F52D9 = 0;
    unk_6F52DA = 0;
  }
  return rf_browser_animate_and_draw();
}

