// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040B2D0 sub_40B2D0
// UNREALRED VERIFIED [ai-script-animation-release-20261013] Combat transition is a distinct owner of animation release: after its owner/AI flag/dead/target-type/mode/alarm/weapon eligibility gates, clear custom-state bit 0x02000000. Mode 11 writes secondary state 9; other admitted modes cancel tracked actions and scripted context, clear pending state and clear scheduler bit 8. Do not attach this bit-8 clear to generic Goto or numeric mode writes.
// UNREALRED VERIFIED [lan-ai-relations-20261028] The same-friendliness peer directional-admission propagation inside this combat transition is skipped when either multiplayer-runtime or split-screen is active. Only the both-zero branch scans same-friendliness peers in represented modes 2/4 and writes 0x20000 at entity+0x7D0. This is not evidence that all synthetic LAN AI participants share a squad or destination reservation.
// UNREALRED VERIFIED [ai-target-commit-20261029] Combat-transition decisions read the current stored identifier AI[176]/+0x2C0 (including 0x41E2C0, repeated entity resolution, route/range decisions), not a candidate argument to the target setter. Host combat code must revalidate its requested target after callback-producing writes before using cached candidate position/velocity or firing. This does not establish a native callback serial; that is Unreal adapter ownership protection.
// UNREALRED VERIFIED [combat-reaction-20261111]: Owner full-handle entity resolution and AI+530 bit40000000/dead gates precede41E2C0 current-target common-type7 resolution. A genuine type7 target restores40A2A0 BEFORE current-mode17 rejection. A dead type0 entity or a host corpse presentation is not automatically type7.
void __cdecl sub_40B2D0(int *a1)
{
  double v1; // st7
  float v2[3]; // [esp+0h] [ebp-24h] BYREF
  float v3; // [esp+Ch] [ebp-18h]
  int i; // [esp+10h] [ebp-14h]
  int v5; // [esp+14h] [ebp-10h]
  int v6; // [esp+18h] [ebp-Ch]
  int v8; // [esp+20h] [ebp-4h]

  v5 = rf_entity_resolve_handle(*(_DWORD *)(*a1 + 44));
  if ( v5 && (a1[332] & 0x40000000) == 0 && !rf_entity_is_dead(v5) )
  {
    if ( rf_corpse_resolve_handle_type7(a1[176]) )
    {
      sub_40A2A0(a1);
      return;
    }
    if ( a1[160] != 17 && sub_40AEB0(a1) != 1 && sub_40B6D0((_DWORD *)(v5 + 672)) )
    {
      *(_DWORD *)(v5 + 2064) &= ~0x2000000u;
      if ( a1[160] == 11 )
      {
        rf_ai_secondary_state_write((int)a1, 9);
        return;
      }
      rf_ai_cancel_tracked_body_action(a1);
      rf_ai_clear_scripted_animation_context(a1);
      *(_DWORD *)(*a1 + 2100) = -1;
      *(_DWORD *)(*a1 + 2064) &= ~8u;
      if ( rf_ai_unholster_pending_flag_set((int)a1) )
        rf_ai_start_pending_unholster_action(a1);
      rf_timestamp_arm_random_inclusive_milliseconds(a1 + 141, 2000, 4000);
      if ( rf_entity_class_flags724_has_mask1(v5) && !rf_entity_uses_fall_or_airborne_vehicle_motion(v5) )
        sub_4355A0(v5);
      if ( !(rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode) )
      {
        for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
        {
          if ( *(_DWORD *)(i + 504) == *(_DWORD *)(*a1 + 504)
            && i != *a1
            && (*(_DWORD *)(i + 1312) == 2 || *(_DWORD *)(i + 1312) == 4)
            && !rf_object_has_respawn_inactive_flag(v5) )
          {
            *(_DWORD *)(i + 2000) |= 0x20000u;
          }
        }
      }
      if ( a1[160] == 3 )
      {
        if ( rf_entity_class_flags724_has_mask800(*a1) )
          return;
      }
      else
      {
        rf_ai_numeric_mode_write(a1, 3, -1, -1);
      }
      v6 = 2;
      if ( rf_ai_primary_flag20_without_secondary((int)a1) )
        v6 = 3;
      v8 = rf_entity_resolve_handle(a1[176]);
      if ( !v8 )
        goto LABEL_43;
      if ( rf_ai_target_needs_route_approach(a1) )
      {
        rf_vector3_default_construct_noop(v2);
        rf_ai_copy_route_target_position((int)a1, v2);
        if ( rf_ai_route_build(*(_DWORD *)(*a1 + 44), (int)v2) == 1 )
          v6 = 1;
      }
      if ( (v3 = rf_vector_distance((const float *)(*a1 + 60), (const float *)(v8 + 60)),
            !rf_ai_primary_range_target_gate((int)a1))
        && (v6 == 2 || v6 == 3)
        && (v1 = rf_ai_resolve_attack_range((int)a1, 1), v3 > v1) )
      {
        rf_ai_select_secondary11_after_reload_or_route_retry(a1);
        if ( a1[173] != 11 && !rf_ai_primary_flag20_without_secondary((int)a1) )
          rf_ai_secondary_state_write((int)a1, 2);
      }
      else
      {
LABEL_43:
        rf_ai_secondary_state_write((int)a1, v6);
      }
    }
  }
}

