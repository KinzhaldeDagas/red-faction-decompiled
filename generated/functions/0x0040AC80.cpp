// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040AC80 sub_40AC80
// UNREALRED VERIFIED [lan-ai-damage-source-20261028] Numeric mode-7 target/timer installation shown below is not the MP path. At entry either multiplayer-runtime or split-screen delegates immediately to 0x402B40, which calls 0x402950 with literal goal string health. The helper scans a bounded matching goal set, chooses one randomly, and on successful 0x4028C0 admission requests numeric mode 4 plus owner flags. Do not infer native multiplayer bot pursuit/retreat timing from the standalone mode-7 branch; full goal data ownership remains outside this pass.
// UNREALRED VERIFIED [combat-reaction-20261111]: Standalone prefix clears AI+530 bit8 BEFORE owner+814 bit10, AI+530 bit40000000, or current-mode17 rejection. Rejected mode17 is therefore not a pure no-op. Multiplayer/split delegates402B40 health-goal BEFORE that prefix. Same-mode7 same-target extends+250 only if remaining<requested duration and returns without mode/target/route rewrite; changed-target path has its own remaining-duration gate.
void __cdecl sub_40AC80(int *Character, int a2, float a3)
{
  int v3; // [esp+4h] [ebp-8h]
  int v4; // [esp+8h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
  {
    rf_ai_choose_health_waypoint_goal(Character);
    return;
  }
  Character[332] &= ~8u;
  if ( (*(_DWORD *)(*Character + 2068) & 0x10) == 0
    && (Character[332] & 0x40000000) == 0
    && Character[160] != 17
    && sub_40AEB0(Character) != 1
    && (sub_40B6D0(Character) != 1 || Character[296] != 2) )
  {
    v4 = rf_object_resolve_handle(a2);
    if ( v4 )
    {
      rf_ai_clear_scripted_animation_context(Character);
      rf_entity_refresh_idle_animation_deadline(*Character);
      rf_entity_stop_weapon_firing(*(_DWORD *)(*Character + 44), Character[1]);
      *(_DWORD *)(*Character + 2064) &= ~0x2000000u;
      *(_DWORD *)(*Character + 2100) = -1;
      v3 = (int)(a3 * 1000.0);
      if ( Character[160] == 7 )
      {
        if ( a2 == Character[176] )
        {
          if ( rf_replicator_signed_remaining_milliseconds(Character + 148) < v3 )
            rf_replicator_arm_milliseconds(Character + 148, v3);
          return;
        }
        if ( rf_replicator_signed_remaining_milliseconds(Character + 148) >= v3 )
          return;
        sub_40BA80(Character, a2);
        rf_replicator_arm_milliseconds(Character + 148, v3);
      }
      else
      {
        rf_replicator_arm_milliseconds(Character + 148, v3);
      }
      rf_ai_numeric_mode_write(Character, 7, -1, -1);
      sub_40BA80(Character, a2);
      if ( !rf_ai_build_avoid_route_with_target_adjustment(*(_DWORD *)(*Character + 44), v4 + 60) )
        rf_ai_selected_weapon_projectile_retarget_or_delay(Character);
    }
  }
}

