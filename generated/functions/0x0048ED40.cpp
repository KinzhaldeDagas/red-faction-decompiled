// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048ED40 rf_multiplayer_runtime_teardown
// UNREALRED VERIFIED [local-multiplayer-20261028] Runtime teardown first notifies/reset peers via0x4A5550/0x4A04F0, closes a surviving client connection, and unregisters internet publication only for authority with flag0x400. It clears multiplayer/server flags, host bit and selected level rotation, reverses temporary multiplayer weapon scaling and marks runtime uninitialized. Leaving a session must not retain remote players or stale ready ownership.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): ABI refinement, full original native body verified: cdecl NO arguments. Entry PUSH ECX only reserves local weapon-loop index DWORD; incoming ECX is never consumed. Local index is explicitly set0 before any read; every object-method ECX is loaded from globals. Removed false thiscall receiver. EAX is0 when initialized704E8C is zero,otherwise final character-cache-release result. Existing teardown ordering/state comments preserved.
int __cdecl rf_multiplayer_runtime_teardown()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = 0;
  if ( unk_704E8C )
  {
    if ( rf_multiplayer_runtime_mode == 1 )
    {
      rf_multiplayer_notify_departure_and_flush();
      rf_network_flush_all_player_queues();
      if ( rf_multiplayer_runtime_mode == 1
        && !rf_multiplayer_server_authority
        && *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16) != -1 )
      {
        rf_reliable_udp_close_peer((_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16), 0);
        *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16) = -1;
      }
      if ( rf_multiplayer_runtime_mode == 1
        && rf_multiplayer_server_authority == 1
        && (rf_multiplayer_game_flags & 0x400) != 0 )
      {
        rf_network_control_poll_state012();
      }
      rf_players_destroy_all_except_local_record();
      rf_clear_startup_session_flag();
      rf_multiplayer_runtime_mode = 0;
      rf_multiplayer_server_authority = 0;
    }
    if ( rf_local_fpgun_player && *(_DWORD *)(rf_local_fpgun_player + 4608) )
      *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) &= ~1u;
    if ( rf_multiplayer_game_mode_get() == 1 )
      rf_multiplayer_reset_motion_globals_77D6D0();
    rf_rfstring_array8_clear_and_release(unk_704F00);
    if ( unk_704E88 )
    {
      for ( i = 0; i < dword_911C68; ++i )
      {
        if ( (rf_weapon_records_flags2[340 * i] & 0x800) != 0 )
          *((float *)&unk_9120C0 + 340 * i) = *((float *)&unk_9120C0 + 340 * i) / 100.0;
      }
      unk_704E88 = 0;
    }
    unk_704E90 = 0;
    sub_5085B0();
    sub_43C4F0();
    rf_item_definitions_select_singleplayer_counts();
    result = rf_multiplayer_character_caches_release();
    unk_757658 = 0;
    unk_704E8C = 0;
  }
  return result;
}

