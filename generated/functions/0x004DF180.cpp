// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DF180 rf_player_request_weapon_switch
// UNREALRED VERIFIED [weapon-autoselect] Validates and requests a player weapon transition, including Remote Charge/detonator resolution and reload, holster, vehicle, turret, and multiplayer gates.
// UNREALRED VERIFIED [weapon-cycle] Consumes committed selector and direct-slot choices through the common validated player weapon-switch path.
void __cdecl rf_player_request_weapon_switch(int a1, int a2, char a3, char a4)
{
  const char *v4; // eax
  std::exception *v5; // [esp+Ch] [ebp-30h]
  _BYTE v6[8]; // [esp+18h] [ebp-24h] BYREF
  int i; // [esp+20h] [ebp-1Ch]
  int v8; // [esp+24h] [ebp-18h]
  int v9; // [esp+28h] [ebp-14h]
  bool v10; // [esp+2Fh] [ebp-Dh]
  int v11; // [esp+38h] [ebp-4h]

  v9 = rf_player_resolve_entity_inventory(a1);
  if ( v9 && (sub_403D00(v9, a2) || a4) )
  {
    v8 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    if ( v8 )
    {
      if ( a2 == dword_911C78 )
      {
        if ( *(int *)(v8 + 4 * dword_912024[340 * dword_911C78] + 684) <= 0 )
          a2 = unk_911C88;
        for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
        {
          if ( *(_DWORD *)(i + 664) == dword_911C78
            && *(_DWORD *)(i + 48) == *(_DWORD *)(v8 + 44)
            && *(float *)(i + 668) > 0.0
            && (*(_DWORD *)(i + 124) & 2) == 0 )
          {
            a2 = unk_911C88;
            break;
          }
        }
      }
      if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
      {
        if ( (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority != 1 || a1 == rf_local_fpgun_player)
          && (!rf_entity_reload_in_progress(v8) || a4)
          && !rf_entity_weapon_is_holstered_for_actions(v8)
          && !rf_entity_has_attached_use_vehicle(v8)
          && !rf_entity_has_attached_use_turret(v8)
          && (!rf_player_has_flags16_mask10(a1) || sub_4EF770() != 1) )
        {
          if ( a2 >= 0 )
          {
            if ( a2 == dword_911C78 )
              rf_local_fpgun_mark_remote_charge_selected();
            if ( a2 == rf_weapon_index_grenade && *(int *)(v8 + 4 * dword_912024[340 * a2] + 684) <= 0 )
            {
              if ( rf_player_has_flags16_mask10(a1) )
                rf_gamesound_play_event(2, 0, 0.0, 1.0);
            }
            else
            {
              if ( rf_entity_selected_weapon_state_bit_is_set(v8, a2) && a2 == dword_911CC4 )
                a2 = unk_911C98;
              if ( *(_DWORD *)(a1 + 3968) != a2 )
              {
                v10 = 0;
                if ( a2 >= dword_911C7C )
                  v10 = *(_DWORD *)(v9 + 8) == a2;
                else
                  v10 = *(_DWORD *)(v9 + 4) == a2;
                if ( !v10 || a4 )
                {
                  if ( sub_403D00(v9, a2) || rf_weapon_has_detonator_flag(a2) )
                  {
                    rf_player_set_pending_weapon_and_disarm_timer184(a1, a2);
                    if ( !a3 )
                      rf_fpgun_request_holster_action(a1);
                  }
                  if ( rf_player_get_alt_zoom_in_flag_byte(a1) )
                    rf_player_reset_alt_zoom_state(a1);
                }
                else if ( rf_player_has_flags16_mask10(a1) )
                {
                  v5 = (std::exception *)rf_string_concat_object_cstr(
                                           v6,
                                           (_DWORD *)&rf_weapon_records_display_name + 340 * a2,
                                           unk_88E340);
                  v11 = 0;
                  v4 = rf_string_object_c_str_or_empty(v5);
                  rf_hud_message_enqueue_expand_tokens_and_rearm_head(v4, 0, 0, nullptr);
                  v11 = -1;
                  rf_string_destroy_buffer(v6);
                }
              }
            }
          }
          else if ( rf_player_has_flags16_mask10(a1) )
          {
            rf_hud_message_enqueue_expand_tokens_and_rearm_head("no weapon", 0, 0, nullptr);
            rf_gamesound_play_event(2, 0, 0.0, 1.0);
          }
        }
      }
      else if ( !rf_entity_reload_in_progress(v8) )
      {
        rf_multiplayer_store_powerup_state_byte(a2);
      }
    }
  }
}

