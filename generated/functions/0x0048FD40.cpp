// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048FD40 rf_multiplayer_hud_render
// UNREALRED VERIFIED [multiplayer-hud] Post-gameplay multiplayer HUD dispatcher: chat input, status composition, power-up icons, notification overlay, and the gated server-level-transition notice.
void rf_multiplayer_hud_render()
{
  if ( rf_multiplayer_chat_active_byte_get() == 1 )
    rf_multiplayer_chat_input_prompt_render();
  rf_multiplayer_hud_status_compose();
  if ( rf_ui_panel_stack_current_id() != 34 )
  {
    rf_multiplayer_powerup_icons_render();
    if ( (*(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) & 0x10) != 0 )
      rf_multiplayer_player_labels_draw_disabled();
    if ( rf_multiplayer_runtime_mode == 1
      && !rf_multiplayer_server_authority
      && (*(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) & 0x20) != 0 )
    {
      rf_render_color_set_rgba8(0, 255, 0, 128);
      rf_font_draw_text_screen(0x8000, 10, "Server is loading new level...", -1, dword_182ABBC);
    }
  }
}

