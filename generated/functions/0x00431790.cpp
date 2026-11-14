// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00431790 rf_weapon_reload_request
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Reload reads RAWreserve[AmmoID] including-1secondaryalias, tests exact loaded==activeclip via4363F0 (not >=), stages13A8/13AC/13B0 using wrapping32bit differences/sums. Nonplayer ordinaryweapon restores pendingreserve to pre-stage live value; exact RocketLauncher/shouldercannon exempt. No-reserve NPC branch refills RAWreserve from activeMax (MOV rawDWORD43192A..431930), exceptlaunchers defaultswitch. Runtime-mode/serverauthority bytes govern immediate commit, not merely MP weapon tablechoice.
char __cdecl rf_weapon_reload_request(int a1, char a2, char a3)
{
  char v4; // [esp+Fh] [ebp-21h]
  float v5; // [esp+10h] [ebp-20h]
  BOOL v6; // [esp+14h] [ebp-1Ch]
  int v7; // [esp+18h] [ebp-18h]
  int v8; // [esp+1Ch] [ebp-14h]
  int v9; // [esp+20h] [ebp-10h]
  int v10; // [esp+24h] [ebp-Ch]
  int v11; // [esp+28h] [ebp-8h]
  float *v12; // [esp+2Ch] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority && a1 == dword_681E38 && !a3 )
  {
    rf_client_send_reload_request_with_200ms_throttle47(*(_DWORD *)(a1 + 676));
    return 0;
  }
  v11 = *(_DWORD *)(a1 + 676);
  if ( v11 < 0 )
    return 0;
  if ( rf_entity_has_player_pointer_if_type0(a1) && sub_4363F0(a1) )
    goto LABEL_10;
  v12 = (float *)((char *)&rf_weapon_records + 1360 * v11);
  v6 = 0;
  if ( rf_multiplayer_runtime_mode == 1 )
    v6 = rf_multiplayer_server_authority == 0;
  if ( *(int *)(a1 + 4 * *((_DWORD *)v12 + 9) + 684) > 0 && !sub_4363F0(a1) || v6 )
  {
    if ( sub_438AC0(a1)
      && (rf_fpgun_action_is_active(*(_DWORD *)(a1 + 5168), 0)
       || rf_fpgun_action_is_active(*(_DWORD *)(a1 + 5168), 1u)
       || rf_fpgun_state_is_resident(*(_DWORD *)(a1 + 5168), 2))
      && !a3 )
    {
LABEL_10:
      rf_gamesound_play_event(2, 0, 0.0, 1.0);
      return 0;
    }
    if ( rf_entity_reload_in_progress(a1) )
    {
      return 0;
    }
    else if ( rf_entity_is_dead(a1) )
    {
      return 0;
    }
    else if ( rf_entity_has_attached_use_vehicle(a1) )
    {
      return 0;
    }
    else
    {
      v8 = dword_912024[340 * v11];
      v9 = unk_912088[340 * v11];
      v7 = v9 - *(_DWORD *)(a1 + 4 * v11 + 812);
      v10 = *(_DWORD *)(a1 + 4 * v8 + 684);
      if ( v10 >= v7 )
      {
        *(_DWORD *)(a1 + 5036) = *(_DWORD *)(a1 + 4 * v8 + 684) - v7;
        *(_DWORD *)(a1 + 5032) = v9;
      }
      else
      {
        *(_DWORD *)(a1 + 5036) = 0;
        *(_DWORD *)(a1 + 5032) = *(_DWORD *)(a1 + 4 * v11 + 812) + *(_DWORD *)(a1 + 4 * v8 + 684);
      }
      *(_DWORD *)(a1 + 5040) = v11;
      if ( !rf_object_has_player_flag(a1)
        && *(_DWORD *)(a1 + 676) != rf_weapon_id_rocket_launcher
        && *(_DWORD *)(a1 + 676) != rf_weapon_id_shoulder_cannon )
      {
        *(_DWORD *)(a1 + 5036) = v10;
      }
      rf_replicator_arm_milliseconds((int *)(a1 + 5020), (int)(v12[35] * 666.5999755859375));
      rf_replicator_arm_milliseconds((int *)(a1 + 5024), (int)(v12[309] * 666.5999755859375));
      *(_DWORD *)(a1 + 2064) |= 0x100u;
      if ( sub_438AC0(a1) )
      {
        rf_fpgun_request_reload_action(*(_DWORD *)(a1 + 5168));
        if ( rf_weapon_is_riot_stick(v11) || rf_weapon_has_flame_flag(v11) )
        {
          if ( v12[311] <= 0.0 )
            rf_replicator_reset((_DWORD *)(a1 + 5028));
          else
            rf_replicator_arm_milliseconds((int *)(a1 + 5028), (int)(v12[311] * 1000.0));
        }
      }
      else
      {
        rf_entity_stop_weapon_firing(*(_DWORD *)(a1 + 44), *(_DWORD *)(a1 + 676));
      }
      if ( *(_DWORD *)(a1 + 3268) != -1 )
      {
        v4 = 1;
        if ( rf_object_has_player_flag(a1) )
        {
          rf_ai_propagate_stimulus_to_nearby_entities(*(_DWORD *)(a1 + 44), (float *)(a1 + 60), 12.0, 1);
          v4 = 0;
        }
        rf_entity_request_body_action(a1, 0x27u, 1.0, 0, v4);
        v5 = rf_model_animation_duration_seconds((unsigned int *)*(_DWORD *)(a1 + 128), *(_DWORD *)(a1 + 3268));
        if ( !sub_438AC0(a1) )
          rf_replicator_arm_milliseconds((int *)(a1 + 5020), (int)(v5 * 1000.0));
      }
      *(float *)(a1 + 1972) = *(float *)&dword_6FC428;
      if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      {
        *(_DWORD *)(a1 + 4 * v11 + 812) = *(_DWORD *)(a1 + 5032);
        *(_DWORD *)(a1 + 4 * dword_912024[340 * v11] + 684) = *(_DWORD *)(a1 + 5036);
        rf_server_broadcast_reload_packet46(a1, *(_DWORD *)(a1 + 676), *(_DWORD *)(a1 + 5036), *(_DWORD *)(a1 + 5032));
      }
      return 1;
    }
  }
  else
  {
    if ( rf_entity_has_player_pointer_if_type0(a1) && !a2 )
      rf_gamesound_play_event(2, 0, 0.0, 1.0);
    if ( !rf_object_has_player_flag(a1) )
    {
      if ( *(_DWORD *)(a1 + 676) == rf_weapon_id_rocket_launcher
        || *(_DWORD *)(a1 + 676) == rf_weapon_id_shoulder_cannon )
      {
        rf_ai_switch_to_default_primary_after_launcher_exhaustion((_DWORD *)(a1 + 672));
      }
      else
      {
        *(float *)(a1 + 4 * *((_DWORD *)v12 + 9) + 684) = v12[152];
      }
    }
    if ( *(int *)(a1 + 4 * *((_DWORD *)v12 + 9) + 684) > 0
      && sub_4363F0(a1)
      && rf_multiplayer_runtime_mode == 1
      && rf_multiplayer_server_authority == 1 )
    {
      rf_server_broadcast_reload_packet46(
        a1,
        v11,
        *(_DWORD *)(a1 + 4 * dword_912024[340 * v11] + 684),
        *(_DWORD *)(a1 + 4 * v11 + 812));
    }
    return 0;
  }
}

