// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048DC80 rf_multiplayer_runtime_initialize
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Multiplayer initialization calls5086D0 rf_weapon_apply_multiplayer_runtime_values at48DE30, then4746C0 item active MPcount selection at48DE3A, before subsequent multiplayer world admission. Host Original pickup dispatcher role and active native weapon/item profiles must share this initialization domain, not independently combine MP dispatch with SP caps.
// UNREALRED VERIFIED [combat-native-pickup-callee-correction-20261111]: Corrected the preceding note callee transcription from the actual call instruction48DE30 and exported callee target5086D0. No implementation, name, type, instruction or unrelated comment changes.
void __cdecl rf_multiplayer_runtime_initialize(int a1, int *a2)
{
  int i; // [esp+0h] [ebp-4h]

  if ( !unk_704E8C )
  {
    rf_network_flush_all_receive_queues();
    rf_multiplayer_runtime_mode = 1;
    unk_704BD8 = 0;
    rf_multiplayer_notify_departure_and_flush();
    rf_players_destroy_all_except_local_record();
    if ( rf_multiplayer_runtime_mode == 1
      && !rf_multiplayer_server_authority
      && *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16) != -1 )
    {
      rf_reliable_udp_close_peer((_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16), 0);
      *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16) = -1;
    }
    unk_704E90 = 0;
    rf_network_get_local_endpoint((int)&unk_704EF4);
    if ( byte_704E83 )
    {
      rf_multiplayer_rules_parse();
      sub_48FEF0();
    }
    else
    {
      rf_string_assign_from_cstr(dword_704EC8, (char *)&byte_6393A1);
      rf_multiplayer_game_flags = 0;
      *(_DWORD *)unk_704EDC = 32;
      *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) = 0;
      *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 12) = 0;
      *(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20) = rf_multiplayer_allocate_unused_network_id_byte();
      *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16) = -1;
      *(_DWORD *)(rf_local_fpgun_player + 24) = sub_431680("miner1");
    }
    if ( rf_local_fpgun_player && *(_DWORD *)(rf_local_fpgun_player + 4608) )
      *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) &= ~1u;
    if ( a1 && a2 && rf_local_fpgun_player && *(_DWORD *)(rf_local_fpgun_player + 4608) )
      rf_reliable_udp_connect_to_endpoint((int *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16), a2);
    rf_weapon_apply_multiplayer_runtime_values();
    sub_43C580();
    rf_item_definitions_select_multiplayer_counts();
    if ( !unk_704E88 )
    {
      for ( i = 0; i < dword_911C68; ++i )
      {
        if ( (rf_weapon_records_flags2[340 * i] & 0x800) != 0 )
          *((float *)&unk_9120C0 + 340 * i) = *((float *)&unk_9120C0 + 340 * i) * 100.0;
      }
      unk_704E88 = 1;
    }
    rf_network_flush_all_receive_queues();
    unk_182A378 = 1;
    rf_fpgun_release_cycle_slot_model_cache();
    rf_fpgun_initialize_cycle_slot_model_cache();
    unk_182A378 = 0;
    rf_multiplayer_character_caches_preload();
    unk_704E8C = 1;
  }
}

