// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AE300 rf_splitscreen_match_initialize
// UNREALRED VERIFIED [combat-native-pickup-source-20261111] Split match setup sets split-active byte and creates configured local players/viewport modes; this body does not select active weapon/item table values. Caller4485C0 invokes it late under deferredSplit byte. Separately UI panel18 path4AE510 calls5086D0 after input/unpause. A standalone GetNetMode or split-active byte alone does not prove active table profile; split-only profile remains unresolved.
_DWORD *rf_splitscreen_match_initialize()
{
  _DWORD *result; // eax
  int i; // [esp+8h] [ebp-4h]
  int j; // [esp+8h] [ebp-4h]
  int k; // [esp+8h] [ebp-4h]

  rf_splitscreen_runtime_active = 1;
  unk_7B25D1 = 0;
  if ( rf_splitscreen_local_player_count == 2 )
  {
    if ( rf_local_player_entry_count < 2 && !rf_player_create_runtime(1u) )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\gamesrc\\multi\\multi_splitscreen.cpp",
        582,
        "Cannot create Player 2!");
    if ( !*(_DWORD *)(dword_87C5B4 + 196) )
      rf_camera_allocate_player_slot(dword_87C5B4);
  }
  for ( i = 0; i < rf_splitscreen_local_player_count; ++i )
  {
    if ( !rf_splitscreen_player_entity_create(rf_local_player_entries[i]) )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\gamesrc\\multi\\multi_splitscreen.cpp",
        602,
        "Failed creating player entity!");
  }
  if ( rf_splitscreen_local_player_count == 2 )
  {
    rf_player_viewport_mode_set(rf_local_player_entries[0], 2);
    rf_player_viewport_mode_set(dword_87C5B4, 3);
  }
  else
  {
    rf_player_viewport_mode_set(rf_local_player_entries[0], 0);
  }
  unk_7B25D8 = rf_local_player_entries[0];
  unk_7B25C8 = (double)unk_7B2578 * 60.0;
  unk_7B25DD = unk_7B25C8 == 0.0;
  unk_7B25DE = unk_7B2574 == 0;
  unk_7B25D2 = 0;
  unk_7B25D3 = 0;
  unk_7B25DC = 0;
  result = (_DWORD *)rf_local_players_reset_level_runtime_state();
  for ( j = 0; j < rf_local_player_entry_count; ++j )
    result = (_DWORD *)rf_player_score_record_clear_words2_4_and_byte6(rf_local_player_entries[j]);
  for ( k = 0; k < 16; ++k )
    result = rf_multiplayer_stats32_zero_tail(&unk_757668[21 * k]);
  unk_7B2568 = 0.0;
  unk_7B25CC = 0.0;
  unk_7B25E4 = 0;
  return result;
}

