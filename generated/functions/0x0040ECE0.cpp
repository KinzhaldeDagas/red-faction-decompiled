// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040ECE0 rf_ai_route_update
// UNREALRED VERIFIED [combat-directed-consumers-20261111] Following+strafe reads ownerAI2C0 target FULL COMMON handle through40CE70 and target COMMON+3C for facing; no-route branch resolves target ENTITY through433EE0 and reads Entity7D4. These are distinct common/ref operands and resolver domains; do not unconditionally substitute speech7D4 for following or globalP0 for the retained target. Native common-types beyond represented body registry and native view/physics motion chains remain separate provider requirements.
// UNREALRED VERIFIED [combat-directed-consumers-correction-20261111] Corrected only our preceding resolver address transcription: native entity resolver is433EE0, common resolver40CE70. Following/common3C versus no-route/entity7D4 distinction is unchanged; no production code used the incorrect textual address.
int __cdecl rf_ai_route_update(int a1)
{
  int v2; // esi
  int v3; // esi
  float v4[3]; // [esp+Ch] [ebp-8Ch] BYREF
  float v5[3]; // [esp+18h] [ebp-80h] BYREF
  float v6[3]; // [esp+24h] [ebp-74h] BYREF
  float copy_result[3]; // [esp+30h] [ebp-68h] BYREF
  float v8; // [esp+3Ch] [ebp-5Ch]
  _DWORD *j; // [esp+40h] [ebp-58h]
  _DWORD *i; // [esp+44h] [ebp-54h]
  int v11; // [esp+48h] [ebp-50h]
  int v12; // [esp+4Ch] [ebp-4Ch]
  float target_point[3]; // [esp+50h] [ebp-48h] BYREF
  int v14; // [esp+5Ch] [ebp-3Ch]
  _DWORD *v15; // [esp+60h] [ebp-38h]
  float destination[3]; // [esp+64h] [ebp-34h] BYREF
  int v17; // [esp+70h] [ebp-28h]
  float v18[3]; // [esp+74h] [ebp-24h] BYREF
  int entity; // [esp+80h] [ebp-18h]
  float out_vector[3]; // [esp+84h] [ebp-14h] BYREF
  float v21; // [esp+90h] [ebp-8h] BYREF
  char v22; // [esp+97h] [ebp-1h]

  entity = rf_entity_resolve_handle(*(_DWORD *)(a1 + 304));
  if ( !entity )
    return -1;
  if ( *(float *)(entity + 52) <= 0.0 )
    return -1;
  if ( *(int *)(a1 + 24) < 0 || *(_DWORD *)(a1 + 24) > *(_DWORD *)a1 )
    return -1;
  if ( !rf_replicator_has_elapsed((int *)(a1 + 308)) )
  {
    if ( rf_vector3_length((float *)(a1 + 312)) > 0.0 )
    {
      sub_410920(entity, (const float *)(a1 + 312));
      rf_replicator_reset((_DWORD *)(entity + 1928));
    }
    return 0;
  }
  rf_vector3_zero_return_destination((float *)(a1 + 312));
  if ( *(_DWORD *)(a1 + 324) != -1 )
  {
    v15 = (_DWORD *)rf_mover_resolve_handle(*(_DWORD *)(a1 + 324));
    if ( !rf_mover_key1_gate_is_satisfied(v15) )
    {
      v14 = rf_object_resolve_handle(*(_DWORD *)(entity + 1376));
      if ( v14 )
      {
        rf_vector3_default_construct_noop(target_point);
        rf_object_copy_entity_vector7D4_or_position(v14, target_point);
        sub_410920(entity, target_point);
      }
      return 0;
    }
    *(_DWORD *)(a1 + 324) = -1;
  }
  v17 = entity + 672;
  if ( rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode
    && rf_ai_acquire_probe_and_dispatch_weapon_action(v17) )
  {
    return 0;
  }
  v22 = 1;
  if ( rf_entity_descriptor_mode_is_12_15_13_11_or9(entity) || rf_entity_movement_is_index4_or7(entity) )
    v22 = 0;
  *(_BYTE *)(a1 + 368) = sub_40F320(a1, a1 + 372);
  if ( *(_BYTE *)(a1 + 368) )
  {
    rf_vector3_default_construct_noop(destination);
    if ( (*(_DWORD *)(v17 + 1328) & 8) == 0 || *(_DWORD *)(v17 + 704) == -1 )
    {
      v2 = *(_DWORD *)v17;
      if ( *(char **)(v2 + 2136) == sub_445740(9u)
        || (v3 = *(_DWORD *)v17, *(char **)(v3 + 2136) == sub_445740(7u))
        || rf_entity_has_jeep_flag(*(_DWORD *)v17) )
      {
        rf_vector_copy(destination, v6, (const float *)(a1 + 372));
        destination[1] = *(float *)(*(_DWORD *)v17 + 2008);
      }
      else
      {
        rf_vector_copy(destination, v5, (const float *)(a1 + 372));
      }
    }
    else
    {
      v11 = rf_object_resolve_handle(*(_DWORD *)(v17 + 704));
      if ( v11 )
        rf_vector_copy(destination, copy_result, (const float *)(v11 + 60));
    }
    sub_410920(entity, destination);
    rf_vector_copy((float *)(entity + 1932), v4, destination);
    if ( rf_entity_has_humanoid_flag(entity) && *(_DWORD *)(v17 + 640) == 7 && *(_DWORD *)(entity + 676) == -1 )
    {
      for ( i = (_DWORD *)unk_68211C; i != (_DWORD *)&unk_681E90; i = (_DWORD *)i[163] )
      {
        if ( rf_entity_has_humanoid_flag((int)i) )
        {
          if ( rf_entity_body_state_is_resident((int)i, 13)
            && i != (_DWORD *)entity
            && rf_spheres_overlap_strict(
                 (const float *)(entity + 60),
                 (const float *)i + 15,
                 *(float *)(entity + 120),
                 *((float *)i + 30)) == 1 )
          {
            return -2;
          }
        }
        else if ( rf_object_is_use_vehicle(i)
               && !rf_object_has_respawn_inactive_flag((int)i)
               && rf_spheres_overlap_strict(
                    (const float *)(entity + 60),
                    (const float *)i + 15,
                    *(float *)(entity + 120),
                    *((float *)i + 30)) == 1 )
        {
          return -2;
        }
      }
    }
    else if ( *(_DWORD *)(v17 + 640) == 7 || *(_DWORD *)(v17 + 640) == 3 || *(_DWORD *)(v17 + 640) == 6 )
    {
      for ( j = (_DWORD *)unk_68211C; j != (_DWORD *)&unk_681E90; j = (_DWORD *)j[163] )
      {
        if ( rf_object_is_use_vehicle(j)
          && !rf_object_has_respawn_inactive_flag((int)j)
          && !rf_entity_runtime_enabled_or_resolved_attachment((int)j, -1)
          && j != (_DWORD *)entity
          && rf_spheres_overlap_strict(
               (const float *)(entity + 60),
               (const float *)j + 15,
               *(float *)(entity + 120),
               *((float *)j + 30)) == 1 )
        {
          return -2;
        }
      }
    }
    v21 = 1.0;
    rf_vector_subtract((const float *)(a1 + 372), out_vector, (const float *)(entity + 2004));
    rf_vector_normalize_reciprocal_sqrt(out_vector);
    if ( (*(_DWORD *)(v17 + 1328) & 8) == 0 )
    {
      v8 = rf_vector_dot((float *)(entity + 2040), out_vector);
      if ( v8 >= 0.0 )
        v21 = v8;
      else
        v21 = 0.0;
    }
    if ( rf_entity_class_has_contact_geomod_flag200(entity) && !*(_DWORD *)(entity + 2244) )
      v21 = 0.25;
    rf_float_clamp_in_place(&v21, 0.0, 1.0);
    rf_vector_subtract((const float *)(a1 + 372), v18, (const float *)(entity + 2004));
    rf_ai_accumulate_normalized_world_vector(v17, v18, v21);
    return 0;
  }
  else
  {
    v12 = rf_entity_resolve_handle(*(_DWORD *)(v17 + 704));
    if ( v12 && *(_DWORD *)(v17 + 640) != 7 )
      sub_410920(*(_DWORD *)v17, (const float *)(v12 + 2004));
    return 0;
  }
}

