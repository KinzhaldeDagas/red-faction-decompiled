// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A5BB0 sub_4A5BB0
// UNREALRED VERIFIED [lan-match-flow-20261028] Panel-34 match-end initializer arms deadline 0x7B1514 with exactly 10000 milliseconds (push 0x2710 at 0x4A5BD6). It resets local presentation state and chooses win/loss Foley from per-mode score comparison/DM standing. Do not infer a general draw/tie policy from the sorted-standing branch or treat the 10-second deadline as a world-pause contract.
int ***sub_4A5BB0()
{
  int ***result; // eax
  int v1; // esi
  int v2; // esi
  int team0_score_byte; // esi
  int team1_score_byte; // esi
  int v5; // [esp+10h] [ebp-1Ch]
  int v6; // [esp+14h] [ebp-18h]

  result = (int ***)rf_replicator_arm_milliseconds(&unk_7B1514, 10000);
  if ( rf_local_fpgun_player )
  {
    rf_camera_randomize_sample_index();
    rf_camera_slot_advance_sample_and_set_state6(*(_DWORD *)(rf_local_fpgun_player + 196));
    rf_player_hud_screen_tint_set(rf_local_fpgun_player, 255, 255, 255, 1);
    v5 = rf_multiplayer_game_mode_get();
    if ( v5 )
    {
      if ( v5 == 1 )
      {
        if ( *(_BYTE *)(rf_local_fpgun_player + 48) )
        {
          if ( *(_BYTE *)(rf_local_fpgun_player + 48) != 1 )
            return (int ***)rf_gamesound_play_event(78, 0, 0.0, 1.0);
          v2 = (unsigned __int8)rf_ctf_blue_capture_byte_get();
          if ( v2 <= (unsigned __int8)rf_ctf_red_capture_byte_get() )
            return (int ***)rf_gamesound_play_event(78, 0, 0.0, 1.0);
        }
        else
        {
          v1 = (unsigned __int8)rf_ctf_red_capture_byte_get();
          if ( v1 <= (unsigned __int8)rf_ctf_blue_capture_byte_get() )
            return (int ***)rf_gamesound_play_event(78, 0, 0.0, 1.0);
        }
      }
      else
      {
        if ( v5 != 2 )
          return (int ***)rf_gamesound_play_event(78, 0, 0.0, 1.0);
        if ( *(_BYTE *)(rf_local_fpgun_player + 48) )
        {
          if ( *(_BYTE *)(rf_local_fpgun_player + 48) != 1 )
            return (int ***)rf_gamesound_play_event(78, 0, 0.0, 1.0);
          team1_score_byte = (unsigned __int8)rf_multiplayer_get_team1_score_byte();
          if ( team1_score_byte <= (unsigned __int8)rf_multiplayer_get_team0_score_byte() )
            return (int ***)rf_gamesound_play_event(78, 0, 0.0, 1.0);
        }
        else
        {
          team0_score_byte = (unsigned __int8)rf_multiplayer_get_team0_score_byte();
          if ( team0_score_byte <= (unsigned __int8)rf_multiplayer_get_team1_score_byte() )
            return (int ***)rf_gamesound_play_event(78, 0, 0.0, 1.0);
        }
      }
      return (int ***)rf_gamesound_play_event(80, 0, 0.0, 1.0);
    }
    if ( (dword_7B1504 & 1) == 0 )
    {
      dword_7B1504 |= 1u;
      `eh vector constructor iterator'(
        byte_78C280,
        0x1204u,
        33,
        (void (__thiscall *)(void *))rf_player_construct_owned_members,
        (void (__thiscall *)(void *))rf_player_destroy_owned_members);
      atexit(rf_static_destroy_array_0078c280);
    }
    v6 = rf_player_runtime_list_count();
    result = rf_scoreboard_build_sorted_player_snapshots((int ***)byte_78C280, (_DWORD *)dword_87C324, v6);
    if ( v6 < 2 )
      return (int ***)rf_gamesound_play_event(78, 0, 0.0, 1.0);
    if ( *(char **)byte_78C280 != byte_78C280 )
    {
      if ( result == *(int ****)byte_78C280 )
        return (int ***)rf_gamesound_play_event(80, 0, 0.0, 1.0);
      return (int ***)rf_gamesound_play_event(78, 0, 0.0, 1.0);
    }
  }
  return result;
}

