// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048EF50 sub_48EF50
// UNREALRED VERIFIED [lan-match-flow-20261028] Multiplayer per-level reset called by 0x448190 during the panel-5 load chain before RFL load. Across the all-player circular list, copy the 16-bit current-frag word score(Player+0x2C)+2 to score+0, then clear score+2 (frags) and score+4 (captures). Meaning of score+0 beyond this previous-frag copy is not assigned here. Existing player records survive this reset. In contrast, local reset 0x4DBEF0 skips its three score-word clears when multiplayer runtime is active.
void sub_48EF50()
{
  int v0; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  rf_respawn_reset_counts();
  rf_multiplayer_reset_update_handle_cache();
  rf_multiplayer_score_assets_initialize();
  rf_respawn_reset_counts();
  rf_multiplayer_reset_motion_globals_77D6D0();
  rf_multiplayer_clear_two_team_score_bytes();
  rf_multiplayer_hud_reset_state_and_announce_team();
  rf_powerup_nodes_destroy_all();
  unk_704EE0 = 0;
  for ( i = dword_87C324; i; i = v0 )
  {
    **(_WORD **)(i + 44) = *(_WORD *)(*(_DWORD *)(i + 44) + 2);
    *(_WORD *)(*(_DWORD *)(i + 44) + 2) = 0;
    *(_WORD *)(*(_DWORD *)(i + 44) + 4) = 0;
    if ( *(_DWORD *)i == dword_87C324 )
      v0 = 0;
    else
      v0 = *(_DWORD *)i;
  }
  rf_reset_global_dword6663D4();
}

