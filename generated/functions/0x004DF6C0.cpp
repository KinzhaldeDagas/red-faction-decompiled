// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DF6C0 rf_player_handle_weapon_fire_input
// UNREALRED VERIFIED [mission-unhide-20261020] Player weapon input resolves its entity then rejects common inactive before reload/fire admission. UnrealRed guards held input, direct fire handling, character fire notifications and ammo cost against inactive entities; hiding also stops current continuous fire.
void __cdecl rf_player_handle_weapon_fire_input(int a1, char a2, char a3)
{
  unsigned int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  float *v9; // eax
  float scaled_result[3]; // [esp+Ch] [ebp-7Ch] BYREF
  float v11; // [esp+18h] [ebp-70h]
  int j; // [esp+1Ch] [ebp-6Ch]
  float sum_result[3]; // [esp+20h] [ebp-68h] BYREF
  float lhs[3]; // [esp+2Ch] [ebp-5Ch] BYREF
  _BYTE v15[24]; // [esp+38h] [ebp-50h] BYREF
  float vector[3]; // [esp+50h] [ebp-38h] BYREF
  float v17; // [esp+5Ch] [ebp-2Ch]
  float action_animation_duration; // [esp+60h] [ebp-28h]
  int v19; // [esp+64h] [ebp-24h]
  int i; // [esp+68h] [ebp-20h]
  int v21; // [esp+6Ch] [ebp-1Ch]
  char v22; // [esp+73h] [ebp-15h]
  int v23; // [esp+74h] [ebp-14h]
  unsigned int v24; // [esp+78h] [ebp-10h]
  char *v25; // [esp+7Ch] [ebp-Ch]
  _DWORD *v26; // [esp+80h] [ebp-8h]
  _DWORD *v27; // [esp+84h] [ebp-4h]

  if ( rf_player_has_flags16_mask10(a1) )
  {
    v27 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    if ( v27 )
    {
      if ( !rf_object_has_respawn_inactive_flag((int)v27)
        && !rf_entity_reload_in_progress((int)v27)
        && (a2 != 1
         || rf_entity_has_attached_use_vehicle((int)v27)
         || rf_weapon_has_alt_fire_flag(v27[169])
         || rf_weapon_has_alt_custom_mode(v27[169]))
        && (!unk_87C6E4 || rf_vfx_get_remaining_time((const void *)dword_87C6E0, 0) <= 0.0)
        && (!rf_fpgun_weapon_transition_blocks_fire(a1)
         || rf_entity_has_attached_use_vehicle((int)v27)
         || rf_entity_has_attached_use_turret((int)v27))
        && !rf_fpgun_custom_action_busy(a1)
        && (!rf_entity_weapon_is_holstered_for_actions((int)v27) || rf_entity_has_attached_use_vehicle((int)v27))
        && (!rf_weapon_is_riot_stick(v27[169])
         || (!rf_weapon_selected_mode_is_continuous_exact_selector(v27[169], a2 == 0)
          || !rf_entity_weapon_firing_byte_is_set(v27[11], v27[169]))
         && (!a2 || !rf_entity_runtime_flags810_has_mask2000((int)v27))) )
      {
        if ( rf_player_view_target_is_monitor(a1) )
        {
          rf_player_exit_monitor_view(a1);
          rf_replicator_arm_milliseconds(v27 + 302, 100);
          return;
        }
        v21 = (int)v27;
        v26 = (_DWORD *)rf_entity_resolve_handle(v27[128]);
        if ( v26 && (rf_object_get_use_classification(v26) == 4 || rf_object_get_use_classification(v26) == 1) )
          v21 = (int)v26;
        if ( *(int *)(v21 + 676) >= 0
          && !rf_entity_is_dead((int)v27)
          && !rf_entity_is_dead(v21)
          && (!rf_entity_has_jeep_flag(v21) || rf_entity_is_parent_jeep_relation1((int)v27)) )
        {
          if ( rf_weapon_is_semiautomatic(*(_DWORD *)(v21 + 676)) )
          {
            if ( !a3 )
              return;
            rf_replicator_arm_milliseconds((int *)(v21 + 1208), 0);
          }
          if ( rf_entity_has_attached_use_vehicle((int)v27) )
          {
            if ( a2 == 1 && !rf_replicator_has_elapsed((int *)(v21 + 1212)) )
              return;
          }
          else if ( !rf_replicator_has_elapsed((int *)(v21 + 1208)) )
          {
            return;
          }
          if ( a2 == 1 && rf_entity_has_attached_use_vehicle((int)v27) )
          {
            if ( !rf_replicator_has_elapsed((int *)(v21 + 1212)) )
              return;
          }
          else if ( !rf_replicator_has_elapsed((int *)(v21 + 1208)) )
          {
            return;
          }
          v24 = *(_DWORD *)(v21 + 676);
          v19 = rf_weapon_fire_wait_milliseconds(*(_DWORD *)(v21 + 676), a2);
          if ( a2 != 1
            || v24 != rf_weapon_id_flamethrower
            || !rf_entity_weapon_firing_byte_is_set(v27[11], v24)
            && v27[dword_912024[340 * v24] + 171] >= unk_912088[340 * v24] )
          {
            if ( a2 && (v24 == rf_weapon_id_shoulder_cannon || v24 == unk_911C80) )
            {
              if ( a3 )
                rf_gamesound_play_event(2, 0, 0.0, 1.0);
            }
            else
            {
              if ( a2 == 1 )
                v4 = *(_DWORD *)(a1 + 16) | 0x20;
              else
                v4 = *(_DWORD *)(a1 + 16) & 0xFFFFFFDF;
              *(_DWORD *)(a1 + 16) = v4;
              if ( a2 == 1 && rf_weapon_has_alt_custom_mode(v24) )
              {
                if ( rf_weapon_selected_mode_is_continuous_exact_selector(v24, 0)
                  && rf_entity_weapon_firing_byte_is_set(v27[11], v24) )
                {
                  *(_DWORD *)(a1 + 16) &= ~0x20u;
                }
                else if ( a3 == 1 )
                {
                  if ( rf_entity_selected_weapon_state_bit_is_set(v21, v24) )
                    rf_entity_clear_custom_weapon_masks_and_leave_actions((_DWORD *)v21, v24);
                  else
                    rf_entity_set_custom_weapon_masks_and_begin_actions((_DWORD *)v21, v24);
                  if ( *(_DWORD *)(v21 + 2692) != -1 && !rf_entity_body_action_is_active(v21, 3u) )
                    rf_entity_request_body_action(v21, 3u, 1.0, 0, 1);
                  rf_replicator_arm_milliseconds((int *)(v21 + 1208), v19);
                }
              }
              else
              {
                v25 = (char *)&rf_weapon_records + 1360 * v24;
                if ( v21
                  && (*(_DWORD *)(v21 + 2064) & 0x2000) != 0
                  && !rf_weapon_has_underwater_flag(*(_DWORD *)(v21 + 676)) )
                {
                  if ( *(_DWORD *)(v21 + 676) != -1 )
                  {
                    if ( a3 == 1 )
                    {
                      v5 = rf_foley_choose_random_sound(*((_DWORD *)v25 + 92));
                      rf_gamesound_play_positional_event(v5, (float *)(v21 + 60), 1.0, (int)flt_17F10B0, 0);
                      rf_fpgun_request_fire_fail_action(a1);
                    }
                    rf_replicator_arm_milliseconds((int *)(v21 + 1208), v19);
                  }
                }
                else
                {
                  if ( sub_5119F0(v24) )
                  {
                    if ( a2 )
                      *(_DWORD *)(a1 + 4160) = 1;
                    else
                      *(_DWORD *)(a1 + 4160) = 0;
                  }
                  if ( rf_weapon_has_detonator_flag(v24) )
                  {
                    if ( !rf_entity_mark_owned_flag40_projectiles((int)v27) )
                    {
                      v6 = rf_foley_choose_random_sound(*((_DWORD *)v25 + 92));
                      rf_gamesound_play_event(v6, 0, 0.0, 1.0);
                    }
                    action_animation_duration = rf_fpgun_get_action_animation_duration(a1, 0);
                    rf_replicator_arm_milliseconds((int *)(a1 + 184), (int)(action_animation_duration * 1000.0 + 0.5));
                    dword_87C648 = dword_911C78;
                    rf_fpgun_request_fire_action(a1, 0);
                    rf_player_autoswitch_exhausted_weapon(a1, a2);
                    rf_replicator_arm_milliseconds((int *)(v21 + 1208), v19);
                    if ( rf_multiplayer_runtime_mode == 1 )
                      rf_multiplayer_publish_weapon_fire(v27, flt_17F10B0, flt_17F10EC, unk_911C88, 0);
                  }
                  else
                  {
                    if ( rf_entity_class_flags724_has_mask800(v21) && sub_436310(v21) <= 0 )
                      rf_entity_add_weapon_ammo(v21, *(_DWORD *)(v21 + 676), unk_912260[340 * *(_DWORD *)(v21 + 676)]);
                    v22 = 0;
                    v23 = -1;
                    if ( !rf_object_is_use_vehicle((_DWORD *)v21)
                      || !a2
                      || rf_entity_sum_selected_secondary_loaded_and_reserve(v21) > 0 )
                    {
                      goto LABEL_158;
                    }
                    v22 = 1;
                    if ( *(int *)(v21 + 680) >= 0 )
                      v23 = unk_912170[340 * *(_DWORD *)(v21 + 680)];
                    if ( !rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(v21 + 44), *(_DWORD *)(v21 + 676)) )
                    {
LABEL_158:
                      if ( (*((_DWORD *)v25 + 153) & 0x20) == 0 && sub_436310(v21) <= 0 )
                      {
                        if ( rf_object_is_player_associated(v21) )
                        {
                          v22 = 1;
                          if ( *(int *)(v21 + 676) >= 0 )
                            v23 = unk_912170[340 * *(_DWORD *)(v21 + 676)];
                        }
                      }
                      if ( a2 )
                      {
                        if ( rf_weapon_is_riot_stick(v24) && sub_436310(v21) <= 0 )
                        {
                          v22 = 1;
                          if ( *(int *)(v21 + 676) >= 0 )
                            v23 = unk_912170[340 * *(_DWORD *)(v21 + 676)];
                        }
                      }
                      if ( rf_weapon_has_flame_flag(v24) && !sub_436310(v21) )
                      {
                        v22 = 1;
                        if ( *(int *)(v21 + 676) >= 0 )
                          v23 = unk_912170[340 * *(_DWORD *)(v21 + 676)];
                      }
                      if ( v22 )
                      {
                        if ( a3 == 1 )
                        {
                          if ( v23 == -1 )
                          {
                            rf_gamesound_play_event(2, 0, 0.0, 1.0);
                          }
                          else
                          {
                            v7 = rf_foley_choose_random_sound(v23);
                            rf_gamesound_play_event(v7, 0, 0.0, 1.0);
                          }
                        }
                        rf_entity_stop_weapon_firing(*(_DWORD *)(v21 + 44), v24);
                        v8 = rf_int_min_signed(200, v19);
                        rf_replicator_arm_milliseconds((int *)(v21 + 1208), v8);
                        if ( rf_entity_has_turret_flag(v21) || rf_object_is_use_vehicle((_DWORD *)v21) )
                          rf_player_autoswitch_exhausted_weapon(a1, a2);
                      }
                      else
                      {
                        if ( rf_weapon_has_remote_charge_flag(v24) )
                        {
                          rf_vector3_copy_return_destination(lhs, (float *)(v21 + 2004));
                          rf_matrix3_copy_construct((int)v15, (const void *)(v21 + 2016));
                          v9 = rf_vector_multiply_scalar(vector, scaled_result, 2.0);
                          rf_vector_add(lhs, sum_result, v9);
                          if ( rf_geometry_segment_is_obstructed(lhs, sum_result, 1, nullptr) == 1 )
                            a2 = 1;
                          v17 = rf_fpgun_get_action_animation_duration(a1, 0);
                          if ( a2 == 1 )
                            v17 = rf_fpgun_get_action_animation_duration(a1, 1u);
                          v17 = v17 - 0.1000000014901161;
                          rf_replicator_arm_milliseconds((int *)(a1 + 184), (int)(v17 * 1000.0 + 0.5));
                          dword_87C648 = unk_911C88;
                        }
                        if ( rf_weapon_has_positive_impact_delay(v24, a2) != 1 || rf_entity_class_flag1000(v21) )
                        {
                          if ( a2 == 1 && rf_entity_has_attached_use_vehicle((int)v27) )
                          {
                            rf_entity_fire_secondary_or_begin_charge((_DWORD *)v21, 0);
                          }
                          else if ( !rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(v21 + 44), v24) )
                          {
                            sub_431FD0(*(float *)&v21, 0, a2, nullptr, nullptr, nullptr);
                            rf_alarm_rearm_shared_deadline();
                          }
                          if ( rf_multiplayer_runtime_mode && !rf_replicator_is_armed((_DWORD *)(v21 + 1208)) )
                            rf_replicator_arm_milliseconds((int *)(v21 + 1208), 100);
                          *(float *)(a1 + 4032) = 0.0;
                          for ( i = dword_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
                            *(_DWORD *)(i + 2000) |= 0x80000u;
                        }
                        else
                        {
                          if ( rf_weapon_is_riot_stick(v24) && a2 == 1 )
                            sub_431FD0(*(float *)&v27, 0, 1, nullptr, nullptr, nullptr);
                          else
                            rf_fpgun_request_fire_action(a1, a2);
                          rf_replicator_arm_milliseconds((int *)(v21 + 1208), v19);
                          for ( j = 0; j < 2; ++j )
                          {
                            if ( a2 )
                            {
                              v11 = *(float *)&v25[4 * j + 344];
                              *((_BYTE *)v27 + 1224) = 1;
                            }
                            else
                            {
                              v11 = *(float *)&v25[4 * j + 336];
                              *((_BYTE *)v27 + 1224) = 0;
                            }
                            if ( v11 > 0.0 )
                              rf_replicator_arm_milliseconds(&v27[j + 304], (int)(v11 * 1000.0));
                          }
                          rf_entity_request_body_fire_action((int)v27, a2);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

