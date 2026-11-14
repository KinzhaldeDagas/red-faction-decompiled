// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E1060 rf_player_dispatch_action_input
// UNREALRED VERIFIED [trigger-use-20261021] Input action2 branch calls4DF040 Use forwarding. This branch alone does not establish pressed-versus-held/repeat production; no repeat cadence is inferred or changed in UnrealRed from this evidence.
void __usercall rf_player_dispatch_action_input(double a1@<st0>, int a2, void *a3, char a4)
{
  int v4; // eax
  _DWORD *v5; // [esp+14h] [ebp-4h]

  v5 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(a2 + 20));
  if ( rf_multiplayer_runtime_mode && rf_ui_panel_stack_current_id() == 34 && a3 != (void *)9 && a3 != (void *)10 )
    return;
  if ( !v5 || rf_entity_is_dead((int)v5) && rf_multiplayer_runtime_mode == 1 )
  {
    switch ( (unsigned int)a3 )
    {
      case 0u:
      case 1u:
        if ( rf_multiplayer_runtime_mode != 1 )
          goto LABEL_16;
        if ( rf_replicator_has_elapsed(&rf_manual_respawn_gate_event) )
        {
          rf_replicator_reset(&rf_manual_respawn_gate_event);
          if ( rf_multiplayer_server_authority == 1 )
            rf_server_respawn_player(a2);
          else
            rf_client_send_respawn_request(*(_DWORD *)(a2 + 3932), *(_BYTE *)(*(_DWORD *)(a2 + 4608) + 20));
        }
        else
        {
          if ( !rf_replicator_is_armed(&rf_manual_respawn_gate_event) )
            rf_replicator_arm_milliseconds(&rf_manual_respawn_gate_event, 1000);
LABEL_16:
          if ( rf_splitscreen_runtime_active && *(float *)(a2 + 4596) > 1.0 )
            rf_splitscreen_begin_player_respawn_fade(a2);
        }
        break;
      case 9u:
        goto LABEL_20;
      case 0xAu:
        goto LABEL_21;
      default:
        return;
    }
    return;
  }
  switch ( (unsigned int)a3 )
  {
    case 0u:
      if ( rf_weapon_selector_is_open )
      {
        rf_player_request_weapon_switch(
          a2,
          rf_weapon_cycle_slots_weapon_index[4 * rf_weapon_selector_current_cycle_slot],
          0,
          0);
        rf_weapon_selector_is_open = 0;
        rf_replicator_arm_milliseconds(v5 + 302, 400);
        rf_gamesound_play_event(rf_weapon_selector_select_sound_event, 0, 0.0, 1.0);
      }
      else if ( !rf_entity_is_carrying_body((int)v5) )
      {
        rf_player_handle_weapon_fire_input(a2, 0, a4);
      }
      return;
    case 1u:
      if ( rf_weapon_selector_is_open )
      {
        rf_weapon_selector_is_open = 0;
        rf_replicator_arm_milliseconds(v5 + 302, 400);
        rf_gamesound_play_event(rf_weapon_selector_off_sound_event, 0, 0.0, 1.0);
        return;
      }
      if ( rf_entity_is_carrying_body((int)v5) )
        return;
      if ( rf_entity_has_attached_use_vehicle((int)v5) || rf_player_view_target_is_monitor(a2) )
      {
        if ( a4 )
        {
          v4 = rf_entity_resolve_handle(v5[128]);
          if ( rf_entity_class_flag1000(v4) )
          {
            rf_player_cycle_vehicle_camera_and_play_sound(a2);
            return;
          }
        }
        goto LABEL_49;
      }
      if ( rf_weapon_has_alt_zoom_flag(v5[169]) )
      {
        if ( a4 == 1 || *(_BYTE *)(a2 + 4428) == 1 && rf_replicator_has_elapsed(v5 + 302) )
        {
          rf_player_toggle_alt_zoom(a2);
          *(_BYTE *)(a2 + 4428) = 0;
        }
        return;
      }
      if ( rf_weapon_has_alt_lock_flag(v5[169]) )
      {
        if ( rf_multiplayer_runtime_mode )
        {
          rf_player_handle_weapon_fire_input(a2, 0, a4);
        }
        else if ( a4 == 1 )
        {
          rf_player_request_target_lock_scan(a2);
        }
        return;
      }
      if ( !rf_weapon_has_scanner_flag(v5[169]) )
      {
LABEL_49:
        rf_player_handle_weapon_fire_input(a2, 1, a4);
        return;
      }
      if ( a4 == 1 )
        rf_player_toggle_scanner_flag(a2);
      return;
    case 2u:
      rf_player_dispatch_use_if_nonnull(a1, (_DWORD *)a2);
      return;
    case 3u:
      if ( rf_player_has_live_entity_outside_monitor_and_turret(a2) && !rf_input_get_scan_code_state_byte(41) )
        rf_entity_try_jump_launch((int)v5);
      return;
    case 4u:
      if ( *(_BYTE *)(a2 + 3896) )
      {
        if ( *(_BYTE *)(a2 + 177) || !rf_player_entity_mode1_or3_without_use_attachments(a2) )
        {
          if ( *(_BYTE *)(a2 + 177) && rf_entity_try_apply_standing_shape_centers((int)v5) )
          {
            *(_BYTE *)(a2 + 177) = 0;
            sub_4344D0((int)v5, 1);
          }
        }
        else
        {
          rf_entity_apply_crouch_shape_centers((int)v5);
          *(_BYTE *)(a2 + 177) = 1;
          sub_4344D0((int)v5, 0);
          rf_entity_request_body_state((int)v5, 9u, 0.25);
        }
      }
      return;
    case 5u:
      if ( !rf_splitscreen_runtime_active
        && !rf_multiplayer_runtime_mode
        && !rf_fpgun_custom_action_busy(a2)
        && !rf_entity_reload_in_progress((int)v5)
        && !rf_entity_has_attached_use_vehicle((int)v5)
        && !rf_entity_is_carrying_body((int)v5)
        && !rf_entity_has_attached_use_turret((int)v5) )
      {
        if ( rf_entity_weapon_is_holstered_for_actions((int)v5) )
          rf_entity_clear_holster_if_mapped_weapon_owned(v5);
        else
          rf_entity_try_set_holster_and_stop_primary(v5);
      }
      return;
    case 6u:
      if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
      {
        if ( rf_player_weapon_action_context_is_available(a2) )
          rf_weapon_reload_request((int)v5, 0, 0);
      }
      else
      {
        rf_weapon_reload_request((int)v5, 0, 0);
      }
      return;
    case 7u:
      rf_player_cycle_weapon_next(a2, -1, 1);
      return;
    case 8u:
      rf_player_cycle_weapon_previous(a2, -1, 1);
      return;
    case 9u:
LABEL_20:
      rf_multiplayer_chat_begin_mode(0);
      return;
    case 0xAu:
LABEL_21:
      rf_multiplayer_chat_begin_mode(1u);
      return;
    case 0x15u:
      if ( !rf_splitscreen_runtime_active
        && !rf_multiplayer_runtime_mode
        && !rf_player_resolved_entity_is_dead(a2)
        && !rf_player_has_no_resolved_entity(a2)
        && rf_ui_pending_panel_id_get() != 10
        && *(float *)(rf_local_fpgun_player + 4564) <= 0.0 )
      {
        if ( rf_ui_panel_stack_current_id() == 20 )
          rf_ui_request_panel_stack_pop();
        else
          rf_ui_request_panel_deferred(20, 1, 1);
      }
      return;
    case 0x17u:
      rf_quicksave_request(a3);
      return;
    case 0x18u:
      rf_quickload_request();
      return;
    case 0x19u:
      rf_player_cycle_weapon_next(a2, 0, 1);
      return;
    case 0x1Au:
      rf_player_cycle_weapon_next(a2, 1, 1);
      return;
    case 0x1Bu:
      rf_player_cycle_weapon_next(a2, 2, 1);
      return;
    case 0x1Cu:
      rf_player_cycle_weapon_next(a2, 3, 1);
      return;
    case 0x1Du:
    case 0x1Eu:
    case 0x1Fu:
    case 0x20u:
    case 0x21u:
    case 0x22u:
    case 0x23u:
    case 0x24u:
    case 0x25u:
    case 0x26u:
    case 0x27u:
    case 0x28u:
    case 0x29u:
    case 0x2Au:
    case 0x2Bu:
    case 0x2Cu:
    case 0x2Du:
    case 0x2Eu:
    case 0x2Fu:
    case 0x30u:
    case 0x31u:
    case 0x32u:
    case 0x33u:
    case 0x34u:
    case 0x35u:
    case 0x36u:
    case 0x37u:
    case 0x38u:
    case 0x39u:
    case 0x3Au:
    case 0x3Bu:
    case 0x3Cu:
      rf_player_request_weapon_switch(a2, rf_weapon_cycle_slots_weapon_index[4 * ((int)a3 - 29)], 0, 0);
      return;
    default:
      return;
  }
}

