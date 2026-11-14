// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00420140 rf_entity_finalize_death
// UNREALRED VERIFIED [mission-when-dead-20261013] Queues the source Entity for deferred object deletion BEFORE corpse creation. The source old handle lifetime must not depend on successful corpse allocation. A UE visual actor retained to retry a corpse handoff must not remain a logical blocker for the original When_Dead watcher after deferred retirement.
// UNREALRED VERIFIED [combat-burn-owner-20261104]: Burn transfer occurs only after real eligible corpse creation succeeds;43FBF0 owner rebind then corpse+720 association. Missing/suppressed corpse releases untransferred fire owner at finalizer end. Earlier host visual corpse creation must not itself start native fade. Death-action field+0x824 identifies class action slots, separate from live panic.
float *__cdecl rf_entity_finalize_death(int a1)
{
  int v1; // eax
  int v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  char *v6; // eax
  float *result; // eax
  float v8; // [esp+20h] [ebp-F0h]
  float v9; // [esp+24h] [ebp-ECh]
  float v10[3]; // [esp+28h] [ebp-E8h] BYREF
  float v11[3]; // [esp+34h] [ebp-DCh] BYREF
  float v12[3]; // [esp+40h] [ebp-D0h] BYREF
  float v13[3]; // [esp+4Ch] [ebp-C4h] BYREF
  float copy_result[3]; // [esp+58h] [ebp-B8h] BYREF
  float v15[3]; // [esp+64h] [ebp-ACh] BYREF
  int v16; // [esp+70h] [ebp-A0h]
  float v17[3]; // [esp+74h] [ebp-9Ch] BYREF
  float v18[3]; // [esp+80h] [ebp-90h] BYREF
  float v19; // [esp+8Ch] [ebp-84h]
  int v20; // [esp+A4h] [ebp-6Ch]
  int v21; // [esp+ACh] [ebp-64h]
  _DWORD *v22; // [esp+B0h] [ebp-60h]
  float v23[3]; // [esp+C0h] [ebp-50h] BYREF
  float v24[3]; // [esp+CCh] [ebp-44h] BYREF
  _DWORD v25[2]; // [esp+D8h] [ebp-38h] BYREF
  char v26; // [esp+E3h] [ebp-2Dh]
  int containing_point; // [esp+E4h] [ebp-2Ch]
  int v28; // [esp+E8h] [ebp-28h]
  int v29; // [esp+ECh] [ebp-24h]
  int v30; // [esp+F0h] [ebp-20h]
  _DWORD *v31; // [esp+F4h] [ebp-1Ch]
  unsigned __int8 v33; // [esp+FFh] [ebp-11h]
  int i; // [esp+100h] [ebp-10h]
  int v35; // [esp+10Ch] [ebp-4h]

  v33 = 0;
  rf_object_mark_for_deferred_delete(a1);
  if ( rf_object_is_use_vehicle((_DWORD *)a1) )
  {
    for ( i = 0; i < rf_local_player_entry_count; ++i )
    {
      v30 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_player_entries[i] + 20));
      if ( v30 )
      {
        if ( *(_DWORD *)(v30 + 512) == *(_DWORD *)(a1 + 44) )
          rf_damage_dispatch(*(_DWORD *)(v30 + 44), 10000.0, -1, -1, 3, 0, -1, 0);
      }
    }
  }
  if ( (*(_DWORD *)(a1 + 2000) & 0x100000) != 0 )
  {
    v29 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 512));
    if ( v29 )
      rf_damage_dispatch(*(_DWORD *)(v29 + 44), 1000.0, -1, -1, -1, 0, -1, 0);
  }
  if ( rf_entity_resolve_handle(*(_DWORD *)(a1 + 512)) )
    rf_entity_try_detach_with_safe_exit(a1);
  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 2252)); ++i )
  {
    v1 = sub_552200((_DWORD *)(a1 + 2252), i);
    v28 = rf_entity_resolve_handle(*(_DWORD *)(*(_DWORD *)v1 + 4));
    if ( v28 && (*(_DWORD *)(v28 + 2000) & 0x100000) != 0 )
      *(float *)(v28 + 52) = 0.0;
    v2 = sub_552200((_DWORD *)(a1 + 2252), i);
    rf_entity_detach_first_matching_child(a1, *(_DWORD *)(*(_DWORD *)v2 + 4), 1);
  }
  v31 = sub_4DD720(*(_DWORD *)(a1 + 44));
  if ( v31 )
    rf_player_enter_death_transition((int)v31);
  if ( *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1784) != -1 )
  {
    *(_DWORD *)(a1 + 2084) = -1;
    rf_entity_emit_death_explosion_debris(a1);
  }
  if ( (*(_DWORD *)(a1 + 2064) & 0x80) == 0
    && (*(_DWORD *)(a1 + 2084) != -1 || (int)rf_string_length_from_cstr((const char **)(*(_DWORD *)(a1 + 660) + 24)) > 0) )
  {
    rf_string_construct_empty(v25);
    v35 = 0;
    if ( *(_DWORD *)(a1 + 2084) != -1 && *(int *)(a1 + 16 * *(_DWORD *)(a1 + 2084) + 2648) > -1 )
      rf_string_assign_from_object(
        v25,
        *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1888) + 52 * *(_DWORD *)(a1 + 16 * *(_DWORD *)(a1 + 2084) + 2648));
    v26 = 1;
    containing_point = rf_push_region_find_containing_point((const float *)(a1 + 60));
    if ( containing_point && (*(_DWORD *)(containing_point + 8) & 2) != 0 )
      v26 = 0;
    if ( v26 && *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) != 10 )
    {
      rf_vector3_default_construct_noop(v23);
      rf_vector3_default_construct_noop(v24);
      v9 = *(float *)(a1 + 64) + 0.5;
      rf_vector3_set_components_thiscall(v23, *(float *)(a1 + 60), v9, *(float *)(a1 + 68));
      v8 = *(float *)(a1 + 64) - 1.5;
      rf_vector3_set_components_thiscall(v24, *(float *)(a1 + 60), v8, *(float *)(a1 + 68));
      rf_physics_hit_record_construct_noop((char *)v17);
      v19 = 1.0;
      v21 = 0;
      v20 = -1;
      rf_physics_shape_sweep_movers_and_static_world((int)v23, (int)v24, a1 + 136, (int)v17);
      if ( v19 >= 1.0 )
      {
        if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
          v26 = 0;
      }
      else if ( rf_object_resolve_handle(v20) )
      {
        v26 = 0;
      }
      else if ( v18[1] > 0.5 && v22 && rf_geomod_face_area(v22) > 1.0 )
      {
        v3 = rf_vector_cross(v18, v15, (float *)(a1 + 96));
        rf_vector_copy((float *)(a1 + 72), copy_result, v3);
        rf_vector_normalize((float *)(a1 + 72));
        v4 = rf_vector_cross((float *)(a1 + 72), v13, v18);
        rf_vector_copy((float *)(a1 + 96), v12, v4);
        v5 = rf_vector_cross((float *)(a1 + 96), v11, (float *)(a1 + 72));
        rf_vector_copy((float *)(a1 + 84), v10, v5);
        rf_physics_hit_record68_copy_fields((float *)(a1 + 436), v17);
      }
    }
    if ( v26 )
    {
      v6 = (char *)rf_string_object_c_str_or_empty(v25);
      v16 = rf_corpse_create_from_entity(a1, v6, (float *)(a1 + 60), (float *)(a1 + 72), 0, 0);
      if ( v16 && (*(_DWORD *)(a1 + 2064) & 0x4000000) != 0 )
      {
        rf_corpse_schedule_eviction(v16);
        *(_DWORD *)(a1 + 2064) &= ~0x200u;
      }
      if ( *(_DWORD *)(a1 + 5080) && v16 )
      {
        sub_43FBF0(*(_DWORD *)(a1 + 5080), *(_DWORD *)(v16 + 44));
        *(_DWORD *)(v16 + 720) = *(_DWORD *)(a1 + 5080);
        v33 = 1;
      }
    }
    v35 = -1;
    rf_string_destroy_buffer(v25);
  }
  if ( sub_438AC0(a1)
    && rf_multiplayer_runtime_mode == 1
    && (rf_multiplayer_game_flags & 0x20) == 0
    && rf_ui_panel_stack_current_id() != 34 )
  {
    rf_camera_slot_advance_sample_and_set_state6(*(_DWORD *)(*(_DWORD *)(a1 + 5168) + 196));
  }
  result = (float *)v33;
  if ( !v33 && *(_DWORD *)(a1 + 5080) )
  {
    result = rf_burn_effect_release_record(*(float **)(a1 + 5080), 0);
    *(_DWORD *)(a1 + 5080) = 0;
  }
  return result;
}

