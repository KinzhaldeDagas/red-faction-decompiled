// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004044B0 rf_ai_numeric_mode2_update
// UNREALRED VERIFIED [combat-reaction-target-wait-20261111]: In standalone, after the preceding flinch/state/target/idle gates and retry handling, secondary1 advances the route; otherwise authoredclass ambient bit800000 AND elapsedAI+41C writessecondary1 then40EAB0 randomroute. This consumes the shared route+134 deadline also written by40A2A0. Multiplayer/split instead requestsmode3 beforethis route logic.
// UNREALRED VERIFIED [original-goto-room-20261112]: The call at4044F9 targets486DE0, a pure ECX getter returning common DWORD0 (cached room pointer), not dirty-room refresh. The route/body gate is !room || room BYTE352 || secondary==1. For valid cached-room/null storage, secondary1 determines true independently of BYTE352; ASM still evaluates the earlier byte read when room is nonNULL. No room lookup, traversal or publication effect is hidden in486DE0.
int __cdecl rf_ai_numeric_mode2_update(int *a1)
{
  int result; // eax
  float target_point[3]; // [esp+0h] [ebp-14h] BYREF
  int v3; // [esp+Ch] [ebp-8h]
  int first_dword; // [esp+10h] [ebp-4h]

  result = rf_ai_no_local_player_object_available();
  if ( !(_BYTE)result )
  {
    if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
    {
      return rf_ai_numeric_mode_write(a1, 3, -1, -1);
    }
    else
    {
      first_dword = rf_receiver_get_first_dword((void *)*a1);
      if ( !first_dword || *(_BYTE *)(first_dword + 352) || a1[173] == 1 )
      {
        rf_replicator_arm_milliseconds(a1 + 183, 0);
        if ( !rf_ai_should_seek_replacement_target(a1)
          || (result = rf_ai_scan_and_commit_weighted_target(a1), a1[160] == 2) )
        {
          rf_entity_try_idle_body_variation((_DWORD *)*a1);
          if ( !rf_ai_configured_body_action_is_active(a1) && !rf_entity_body_state_is_resident(*a1, 22) )
          {
            v3 = rf_object_resolve_handle(a1[176]);
            if ( v3 )
            {
              rf_vector3_default_construct_noop(target_point);
              rf_ai_copy_target_point_for_current_movement(a1, v3, target_point);
              sub_410920(*a1, target_point);
            }
          }
          if ( a1[173] == 12 && rf_replicator_has_elapsed(a1 + 140) )
          {
            if ( rf_ai_route_build(*(_DWORD *)(*a1 + 44), (int)(a1 + 275)) == 1 )
            {
              rf_ai_secondary_state_write((int)a1, 1);
            }
            else
            {
              rf_replicator_arm_milliseconds(a1 + 140, 1000);
              rf_ai_route_reset((int)(a1 + 186));
            }
          }
          if ( a1[173] == 1 )
          {
            rf_ai_route_update((int)(a1 + 186));
          }
          else if ( ((unsigned int)&unk_800000 & *(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1828)) != 0
                 && rf_replicator_has_elapsed(a1 + 263) )
          {
            rf_ai_secondary_state_write((int)a1, 1);
            sub_40EAB0(*(_DWORD *)(*a1 + 44));
          }
          rf_ai_update_nearby_holstered_player_speech(a1);
          rf_ai_update_idle_speech_deadline(a1);
          result = rf_replicator_has_elapsed(a1 + 311);
          if ( (_BYTE)result )
          {
            rf_ai_numeric_mode_write(a1, 4, -1, -1);
            return (int)rf_replicator_reset(a1 + 311);
          }
        }
      }
      else
      {
        return rf_entity_refresh_idle_animation_deadline(*a1);
      }
    }
  }
  return result;
}

