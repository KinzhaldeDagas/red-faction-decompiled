// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DAE00 rf_player_use_interaction_dispatch
// UNREALRED VERIFIED [trigger-use-20261021] Use trigger branches run ordinary5051D0(mode1), then auto505720 only when ordinary returns0 (sites4DB069/4DB5BE). Ordinary waiting InsideTime returns0, so it does not suppress auto fallback. Native dispatcher also owns vehicle/body/pickup gates outside the current UnrealRed trigger adapter.
void __usercall rf_player_use_interaction_dispatch(double a1@<st0>, _DWORD *a2, int a3)
{
  float v3[3]; // [esp+10h] [ebp-78h] BYREF
  float v4[3]; // [esp+1Ch] [ebp-6Ch] BYREF
  float v5[3]; // [esp+28h] [ebp-60h] BYREF
  float v6[3]; // [esp+34h] [ebp-54h] BYREF
  float v7[3]; // [esp+40h] [ebp-48h] BYREF
  float v8[3]; // [esp+4Ch] [ebp-3Ch] BYREF
  float copy_result[3]; // [esp+58h] [ebp-30h] BYREF
  int first_dword; // [esp+64h] [ebp-24h]
  char *v11; // [esp+68h] [ebp-20h]
  int v12; // [esp+6Ch] [ebp-1Ch]
  int v13; // [esp+70h] [ebp-18h]
  float *best_use_candidate; // [esp+74h] [ebp-14h]
  int v15; // [esp+78h] [ebp-10h]
  int v16; // [esp+7Ch] [ebp-Ch] BYREF
  float *v17; // [esp+80h] [ebp-8h]
  char v18; // [esp+87h] [ebp-1h]

  v18 = 0;
  if ( *(_DWORD *)(a3 + 512) == -1 )
  {
    best_use_candidate = rf_entity_find_best_use_candidate((_DWORD *)a3, &v16);
    if ( best_use_candidate )
    {
      v15 = rf_entity_resolve_handle(*((_DWORD *)best_use_candidate + 11));
      switch ( rf_object_get_use_classification(best_use_candidate) )
      {
        case 1:
        case 4:
          if ( rf_multiplayer_runtime_mode == 1
            || !v15
            || rf_entity_runtime_enabled_or_resolved_attachment(v15, v16)
            || rf_entity_has_runtime2068_mask800(v15)
            || rf_entity_reload_in_progress(a3)
            || rf_fpgun_weapon_transition_blocks_fire((int)a2)
            || rf_player_entity_has_armed_timer1216_or1220((int)a2)
            || rf_replicator_is_armed(a2 + 46)
            || rf_fpgun_custom_action_busy((int)a2) )
          {
            break;
          }
          if ( *(_DWORD *)(a3 + 676) == unk_911C80 && (*(_DWORD *)(a3 + 2064) & 0x800) == 0 )
          {
            rf_entity_try_set_holster_and_stop_primary((_DWORD *)a3);
            rf_replicator_arm_milliseconds(a2 + 47, 500);
            return;
          }
          if ( (*(_DWORD *)(*(_DWORD *)(v15 + 660) + 1828) & 0x40) == 0 )
            goto LABEL_64;
          first_dword = rf_receiver_get_first_dword((void *)v15);
          if ( first_dword && rf_liquid_room_contains_point(first_dword, v15 + 60) )
          {
            if ( rf_local_fpgun_player && a2 == (_DWORD *)rf_local_fpgun_player )
              rf_audio_set_environment_if_property_extension_enabled("generic");
LABEL_64:
            if ( rf_object_get_use_classification(best_use_candidate) == 1 )
            {
              rf_player_reset_vehicle_camera_and_chaingun_spin((int)a2);
              a2[4] |= 0x400u;
            }
            rf_player_reset_alt_zoom_state((int)a2);
            rf_entity_stop_weapon_firing(*(_DWORD *)(a3 + 44), *(_DWORD *)(a3 + 676));
            rf_vector_copy((float *)(a3 + 5088), v7, (const float *)(a3 + 60));
            rf_vector_inverse_translate_rotate_in_place((float *)(a3 + 5088), v15 + 60, v15 + 72);
            rf_entity_associate_child_with_last_slot_key(v15, *(_DWORD *)(a3 + 44), v16);
            if ( !rf_entity_is_parent_jeep_relation1(a3) )
              rf_ai_numeric_mode_write((_DWORD *)(v15 + 672), 1, -1, -1);
            rf_ai_secondary_state_write(v15 + 672, 0);
            *(_DWORD *)(v15 + 2064) |= 0x10000u;
            *(_DWORD *)(v15 + 2064) &= ~0x20000u;
            sub_4BBF50(v15, 1);
            rf_vector_copy((float *)(v15 + 5172), v6, (const float *)(*(_DWORD *)(v15 + 660) + 108));
            rf_vector_copy((float *)(v15 + 5184), v5, (const float *)(*(_DWORD *)(v15 + 660) + 120));
            if ( rf_entity_is_parent_jeep_relation1(a3) )
            {
              rf_vector_copy((float *)(a3 + 5172), v4, &flt_87C67C);
              rf_vector_copy((float *)(a3 + 5184), v3, &flt_87C68C);
            }
            if ( rf_entity_class_has_angular_decay_flags(v15) )
              rf_object_request_physics_reactivation_flags(v15);
            v18 = 1;
          }
          break;
        case 7:
          if ( rf_trigger_scan_entity(a3, 1) == 1 )
          {
            v18 = 1;
          }
          else if ( rf_trigger_scan_auto_linked_entities_for_player_use(a1, (_DWORD *)a3) == 1 )
          {
            v18 = 1;
          }
          else if ( a2 == (_DWORD *)rf_local_fpgun_player )
          {
            a1 = 0.0;
            rf_gamesound_play_event(2, 0, 0.0, 1.0);
          }
          break;
        case 8:
          if ( rf_multiplayer_runtime_mode != 1
            && (*((_DWORD *)best_use_candidate + 9) != 2
             || ((v13 = rf_projectile_resolve_uid_type2(*((_DWORD *)best_use_candidate + 11))) == 0
              || (v12 = rf_object_resolve_handle(*(_DWORD *)(v13 + 688))) == 0
              || *(_DWORD *)(v12 + 36))
             && *(_DWORD *)(v13 + 48) == a2[5]) )
          {
            if ( sub_403D00(a3 + 672, dword_911C78) )
            {
              v11 = (char *)&rf_weapon_records + 1360 * dword_911C78;
              if ( *(_DWORD *)(a3 + 4 * *((_DWORD *)v11 + 9) + 684) <= *((_DWORD *)v11 + 152) )
                ++*(_DWORD *)(a3 + 4 * dword_912024[340 * dword_911C78] + 684);
            }
            else
            {
              rf_entity_inventory_grant_weapon((int *)(a3 + 672), dword_911C78, -1);
              *(_DWORD *)(a3 + 4 * dword_912024[340 * dword_911C78] + 684) = 1;
            }
            a1 = 1.0;
            rf_gamesound_play_positional_event(12, best_use_candidate + 15, 1.0, (int)flt_17F10B0, 0);
            rf_object_mark_for_deferred_delete((int)best_use_candidate);
            if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
              rf_multiplayer_broadcast_remote_charge_kill_packet36(a2[5], 0);
            if ( *(_DWORD *)(a3 + 676) == unk_911C88 )
              rf_player_request_weapon_switch((int)a2, dword_911C78, 0, 0);
            v18 = 1;
          }
          break;
        default:
          break;
      }
    }
  }
  else
  {
    if ( rf_multiplayer_runtime_mode )
      return;
    v17 = (float *)rf_entity_resolve_handle(*(_DWORD *)(a3 + 512));
    if ( v17 && ((_DWORD)v17[517] & 0x80) != 0 )
    {
      *(_DWORD *)(rf_local_fpgun_player + 16) |= 0x800u;
      if ( a2 == (_DWORD *)rf_local_fpgun_player )
      {
        a1 = 0.0;
        rf_gamesound_play_event(2, 0, 0.0, 1.0);
      }
    }
    else if ( ((_DWORD)v17[106] & 0x4000) != 0 && *((int *)v17 + 1248) < 0 )
    {
      *(_DWORD *)(rf_local_fpgun_player + 16) |= 0x800u;
      if ( a2 == (_DWORD *)rf_local_fpgun_player )
      {
        a1 = 0.0;
        rf_gamesound_play_event(2, 0, 0.0, 1.0);
      }
    }
    else
    {
      if ( rf_entity_try_detach_with_safe_exit(a3) )
      {
        rf_vector_copy((float *)(a3 + 5172), copy_result, (const float *)(*(_DWORD *)(a3 + 660) + 108));
        rf_vector_copy((float *)(a3 + 5184), v8, (const float *)(*(_DWORD *)(a3 + 660) + 120));
        if ( rf_object_is_use_vehicle(v17) )
        {
          *(float *)(a3 + 2172) = v17[537] + v17[543];
          a1 = v17[538] + v17[544];
          *(float *)(a3 + 2152) = a1;
          rf_vector3_zero_return_destination(v17 + 81);
          rf_vector3_zero_return_destination(v17 + 87);
          rf_vector3_zero_return_destination(v17 + 84);
        }
        if ( (rf_object_is_use_vehicle(v17) || rf_entity_has_turret_flag((int)v17))
          && *(_DWORD *)(a3 + 676) == unk_911C80 )
        {
          rf_entity_clear_holster_if_mapped_weapon_owned((_DWORD *)a3);
        }
      }
      v18 = 1;
    }
  }
  if ( !v18
    && !rf_trigger_scan_entity(a3, 1)
    && !rf_trigger_scan_auto_linked_entities_for_player_use(a1, (_DWORD *)a3)
    && a2 == (_DWORD *)rf_local_fpgun_player )
  {
    rf_gamesound_play_event(2, 0, 0.0, 1.0);
  }
}

