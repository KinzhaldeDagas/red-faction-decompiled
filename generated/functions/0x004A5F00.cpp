// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A5F00 sub_4A5F00
// UNREALRED VERIFIED [lan-match-flow-20261028] Panel-34 tick resets local alt-zoom and Player+0xFB0. Only runtime multiplayer mode 1 plus server authority 1 plus elapsed deadline 0x7B1514 requests panel 5. Clients await the next-level packet route. Until then it calls 0x445060(0) and 0x571C90; 0x445060(0) can run ordinary local/world updates, so this is not evidence of a whole-world pause or complete combat freeze. Panel-5 dispatcher 0x4F11E0 calls 0x447BE0 to destroy, initialize, reload and finalize the level.
int sub_4A5F00()
{
  if ( rf_local_fpgun_player && rf_player_get_alt_zoom_in_flag_byte(rf_local_fpgun_player) )
    rf_player_reset_alt_zoom_state(rf_local_fpgun_player);
  if ( rf_local_fpgun_player )
    *(_BYTE *)(rf_local_fpgun_player + 4016) = 0;
  if ( rf_multiplayer_runtime_mode == 1
    && rf_multiplayer_server_authority == 1
    && rf_replicator_has_elapsed(&unk_7B1514) )
  {
    return rf_ui_request_panel_immediate(5, 0);
  }
  rf_game_frame_update_and_render_single_local_view(0);
  return rf_renderer_present_with_full_viewport();
}

