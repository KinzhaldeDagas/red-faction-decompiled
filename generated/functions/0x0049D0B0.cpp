// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049D0B0 rf_multiplayer_hud_status_compose
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): Noarg HUD composer: always renders notification feed first. Panel getter446190()==EXACT34 skips all later work. Otherwise
// suppression=(localPlayer!=NULL AND BYTE757658!=0); split synchronized time, then countdown49D230 with integer/LOW-BYTE !suppression (not a locale facet pointer). Countdown sounds
// still run when suppression true; digit rendering is disabled and composer skips remaining draw/input-independent HUD work. Unsuppressed: render time-left, compact scoreboard(0),
// three-line intro, select target into local player-pointer slot, update/render target notice; query mode, tick team highlight only mode1, render team/CTF status for modes1/2. No own
// runtime/authority gate or packet sending. Prior general HUD notes retained; exact native panel gate and byte argument now resolved.
void rf_multiplayer_hud_status_compose()
{
  bool v0; // [esp+0h] [ebp-10h]
  int v1; // [esp+4h] [ebp-Ch]
  int v2; // [esp+Ch] [ebp-4h] BYREF

  rf_multiplayer_notification_feed_render();
  if ( rf_ui_panel_stack_current_id() != 34 )
  {
    v0 = rf_local_fpgun_player && unk_757658;
    rf_multiplayer_time_left_split();
    rf_multiplayer_countdown_tick_and_render(!v0);
    if ( !v0 )
    {
      rf_multiplayer_time_left_render();
      rf_multiplayer_compact_scoreboard_render(0);
      rf_multiplayer_hud_render_three_line_intro();
      v2 = 0;
      rf_multiplayer_hud_select_target_player(&v2);
      rf_multiplayer_hud_update_target_notice(v2);
      rf_multiplayer_hud_render_target_notice();
      v1 = rf_multiplayer_game_mode_get();
      if ( v1 == 1 )
        rf_multiplayer_hud_tick_team_highlight_alpha();
      if ( v1 == 2 || v1 == 1 )
        rf_multiplayer_team_ctf_status_render();
    }
  }
}

