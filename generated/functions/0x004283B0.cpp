// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004283B0 rf_entity_update_death_completion
// UNREALRED VERIFIED [death-respawn-decode]: Retains a dying entity until immediate finalization, no selected action, or action completion, then calls the death finalizer.
char __cdecl rf_entity_update_death_completion(int a1)
{
  int saved_uid_for_death; // eax
  float *v2; // eax
  float scaled_result[3]; // [esp+1Ch] [ebp-30h] BYREF
  int v5; // [esp+28h] [ebp-24h]
  int v6; // [esp+2Ch] [ebp-20h]
  int v7[3]; // [esp+30h] [ebp-1Ch] BYREF
  float sum_result[3]; // [esp+3Ch] [ebp-10h] BYREF
  bool v9; // [esp+4Bh] [ebp-1h]

  v9 = 0;
  if ( (*(_DWORD *)(a1 + 2064) & 0x80) != 0 )
  {
    v9 = 1;
    rf_disabled_seven_piece_debris_stub();
    if ( *(_DWORD *)(a1 + 5080) )
    {
      rf_burn_effect_release_record(*(float **)(a1 + 5080), 0);
      *(_DWORD *)(a1 + 5080) = 0;
    }
  }
  else
  {
    v9 = *(_DWORD *)(a1 + 2084) == -1 || !rf_entity_body_action_is_active(a1, *(_DWORD *)(a1 + 2084));
  }
  if ( rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(a1 + 44), *(_DWORD *)(a1 + 676)) )
    rf_entity_stop_weapon_firing(*(_DWORD *)(a1 + 44), *(_DWORD *)(a1 + 676));
  saved_uid_for_death = *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1832) & 0x20;
  if ( saved_uid_for_death )
  {
    if ( dword_681E38 )
    {
      LOBYTE(saved_uid_for_death) = rf_replicator_has_elapsed((int *)(a1 + 1208));
      if ( (unsigned __int8)saved_uid_for_death == 1 )
      {
        rf_vector3_default_construct_noop(v7);
        v2 = rf_vector_multiply_scalar((const float *)(a1 + 96), scaled_result, *(float *)(a1 + 120));
        rf_vector_add((const float *)(a1 + 60), sum_result, v2);
        if ( *(float *)(a1 + 120) <= 6.0 )
        {
          if ( rf_segment_sphere_intersection((int)v7, a1 + 60, (int)sum_result, dword_681E38 + 60, 1.5) )
            rf_damage_dispatch(*(_DWORD *)(dword_681E38 + 44), 1600.0, *(_DWORD *)(a1 + 44), -1, -1, 0, -1, 0);
          LOBYTE(saved_uid_for_death) = rf_entity_set_player_linked_perturbation_timer(
                                          *(_DWORD *)(rf_local_fpgun_player + 196),
                                          0.003,
                                          1.0);
        }
        else
        {
          if ( rf_segment_sphere_intersection((int)v7, a1 + 60, (int)sum_result, dword_681E38 + 60, 2.5) )
            rf_damage_dispatch(*(_DWORD *)(dword_681E38 + 44), 1600.0, *(_DWORD *)(a1 + 44), -1, -1, 0, -1, 0);
          LOBYTE(saved_uid_for_death) = rf_entity_set_player_linked_perturbation_timer(
                                          *(_DWORD *)(rf_local_fpgun_player + 196),
                                          0.003,
                                          1.25);
        }
      }
    }
  }
  if ( v9 )
  {
    rf_entity_finalize_death(a1);
    LOBYTE(saved_uid_for_death) = rf_string_equals_case_insensitive(a1 + 24, "masako_endgame");
    if ( (_BYTE)saved_uid_for_death )
    {
      v5 = rf_trigger_find_by_level_id32(4490);
      if ( v5 )
        rf_trigger_set_forward_enabled(v5);
      saved_uid_for_death = rf_mission_event_registry_find_saved_uid_for_death(18371);
      v6 = saved_uid_for_death;
      if ( saved_uid_for_death )
        LOBYTE(saved_uid_for_death) = (unsigned __int8)rf_mission_event_activate_by_uid(*(_DWORD *)(v6 + 48), -1, -1);
    }
  }
  return saved_uid_for_death;
}

