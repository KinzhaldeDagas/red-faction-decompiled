// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A9E0 rf_player_hud_render_ordinary
// UNREALRED VERIFIED [hud-admission-20261027] Instructions 0x44AB33-0x44AB64 test the weapon-status byte and dispatch 0x44F220 BEFORE querying alternate zoom. Positive zoom bypasses messages, player status, world brackets and countdown, but not the already admitted ammo pass. A host renderer combining ammo and health in one helper must not put a zoom early-return ahead of both branches.
// UNREALRED VERIFIED [hud-core-order-20261027] Within the admitted live-body ordinary branch, order is ammo dispatch (0x44AB45), zoom query, ordinary message (0x44AB6B), persona (0x44AB9C), player status (0x44ABB6), multiplayer compact status, world brackets and countdown. Message rendering is inside the same body/master/scanner/owner admission as ammo/status. A host must not draw messages separately after a combined ammo+health helper, which reverses layering and can leave messages active without an ordinary HUD body.
void __cdecl rf_player_hud_render_ordinary(int a1)
{
  const char *v1; // eax
  int v2; // [esp+4h] [ebp-4h]

  if ( unk_6EE698 != 1 )
  {
    if ( *(_BYTE *)(a1 + 3899) )
    {
      if ( !rf_multiplayer_runtime_mode
        || !rf_local_fpgun_player
        || !rf_input_binding_poll_pressed_or_held(rf_local_fpgun_player + 228, 22, nullptr)
        || rf_player_has_no_resolved_entity(rf_local_fpgun_player)
        || rf_player_resolved_entity_is_dead(rf_local_fpgun_player)
        || (rf_multiplayer_full_scoreboard_gate(1), !unk_757658) )
      {
        if ( rf_player_has_no_resolved_entity(a1)
          || rf_player_resolved_entity_is_dead(a1)
          || rf_ui_panel_stack_current_id() == 34 )
        {
          if ( rf_multiplayer_runtime_mode )
          {
            if ( rf_local_fpgun_player )
              rf_multiplayer_full_scoreboard_gate(1);
          }
        }
        else if ( !rf_unhide_global_owner_present() )
        {
          v2 = rf_player_resolve_view_entity_with_monitor_fallback(a1);
          if ( (!v2 || *(_DWORD *)(v2 + 44) == *(_DWORD *)(a1 + 20)) && *(_BYTE *)(unk_87C640 + 4016) != 1 )
          {
            if ( *(_BYTE *)(a1 + 3900) )
              rf_hud_weapon_ammo_dispatch(a1);
            if ( rf_player_query_alt_zoom_factor(a1) <= 0.0 )
            {
              sub_44B360();
              if ( *(_BYTE *)(a1 + 3902)
                || (v1 = rf_string_object_c_str_or_empty(unk_6FC31C), rf_level_name_is_training(v1)) )
              {
                rf_hud_persona_update_and_render(a1);
              }
              if ( *(_BYTE *)(a1 + 3901) )
                rf_hud_player_status_render(a1);
              if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
                rf_multiplayer_full_scoreboard_gate(0);
              rf_hud_world_target_brackets_render(a1);
              if ( rf_mission_countdown_remaining_seconds > 0.0 )
                rf_mission_countdown_hud_render();
            }
          }
        }
      }
    }
  }
}

