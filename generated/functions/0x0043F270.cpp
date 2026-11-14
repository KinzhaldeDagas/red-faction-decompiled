// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043F270 sub_43F270
// UNREALRED VERIFIED [burn-motion-20261029]: Active fire owners require four emitter pointers and a resolvable owner. Live non-fading owners submit per-frame type4 damage with source -1 and weapon -1 through common damage dispatch. Spread runs against the entity list on one shared elapsed deadline (rearmed225ms after list iteration), excludes source, dead/inactive/vehicle/attached-vehicle entities and tests squared distance<=4. Source for spread is the burning body, distinct from anonymous self-burn. Fading owners advance age and call43F840. Full burn ownership, damage geometry, random scalar arithmetic and global iteration ordering are separate from the particle-motion correction.
// UNREALRED VERIFIED [combat-native-followup-20261104]: Smoke emitter processed first at spine, followed by flame midpoint of lower-leg positions, flame spine, flame head. Flame/spread branch tests prior fadeAge<=12, so transferred corpses can spread during first12 fade seconds. Self damage source/weapon are-1 and use float(class+68/random[5,8])*frameDelta; spread uses candidate class+68/random then /4 and burning-body source. After self dispatch rand()%3 writes body+0x824 values5/14/15 even if dispatch became lethal; meaning must not be invented as animation names. Shared225ms timer rearms after the active-list pass.
// UNREALRED VERIFIED [combat-burn-owner-20261104]: Per-record saved-next traversal: append during a non-tail record may be visited later this pass, while append during original tail is deferred. Shared225ms pulse evaluated during list processing and rearmed at end even when empty, with no catch-up loop. Process smoke3 then flames0/1/2 for priorFadeAge<=12; transferred corpse can spread in this interval. Selfdamage uses anonymous source/weapon, spread uses burning body. Post-self-dispatch rand()%3 writes death-action selection slots5/14/15, not a requested live animation. Invalid-owner raw loop after cleanup is unsafe; a host saved-successor/generation safety correction is not a claim to emulate that bug.
// [UnrealRed burn initialization availability 2026-11-12; full original-byte ASM] At43F2F3 checks all4 raw emitter pointers BEFORE owner resolution. AnyNULL jumps saved-next; no emitter-create retry, voice/fade/spread/self-damage update or owner resolution for that record this pass. Thus real native partialNULL can persist until external cleanup. Host geometry/source Unavailable must not become a permanent native missing-emitter mask. Native shared225ms pulse/list semantics remain independent of any explicitly labeled host retry phase.
char sub_43F270()
{
  float *v0; // eax
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  int v4; // esi
  int v5; // esi
  char result; // al
  float v7; // [esp+24h] [ebp-ECh]
  float v8; // [esp+28h] [ebp-E8h]
  float *v9; // [esp+2Ch] [ebp-E4h]
  float v10[3]; // [esp+30h] [ebp-E0h] BYREF
  float sum_result[3]; // [esp+3Ch] [ebp-D4h] BYREF
  float v12[3]; // [esp+48h] [ebp-C8h] BYREF
  float scaled_result[3]; // [esp+54h] [ebp-BCh] BYREF
  float copy_result[3]; // [esp+60h] [ebp-B0h] BYREF
  float out_vector[3]; // [esp+6Ch] [ebp-A4h] BYREF
  float v16; // [esp+78h] [ebp-98h]
  int v17; // [esp+7Ch] [ebp-94h]
  float v18; // [esp+80h] [ebp-90h]
  float *i; // [esp+84h] [ebp-8Ch]
  float v20[3]; // [esp+88h] [ebp-88h] BYREF
  float *v21; // [esp+94h] [ebp-7Ch]
  float destination[3]; // [esp+98h] [ebp-78h] BYREF
  float v23[3]; // [esp+A4h] [ebp-6Ch] BYREF
  int v24; // [esp+B0h] [ebp-60h]
  float scalar; // [esp+B4h] [ebp-5Ch]
  float v26[3]; // [esp+B8h] [ebp-58h] BYREF
  char v27[36]; // [esp+C4h] [ebp-4Ch] BYREF
  float v28[3]; // [esp+E8h] [ebp-28h] BYREF
  float lhs[3]; // [esp+F4h] [ebp-1Ch] BYREF
  float rhs[3]; // [esp+100h] [ebp-10h] BYREF
  float *v31; // [esp+10Ch] [ebp-4h]

  rf_vector3_default_construct_noop(rhs);
  rf_vector3_default_construct_noop(lhs);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v26);
  rf_vector3_default_construct_noop(v28);
  rf_vector3_default_construct_noop(v23);
  rf_matrix3_construct(v27);
  v31 = (float *)unk_6E6508;
  while ( v31 )
  {
    if ( *((_DWORD *)v31 + 14) == unk_6E6508 )
      v9 = nullptr;
    else
      v9 = *((float **)v31 + 14);
    v21 = v9;
    if ( !*(_DWORD *)v31 || !*((_DWORD *)v31 + 1) || !*((_DWORD *)v31 + 2) || !*((_DWORD *)v31 + 3) )
      goto LABEL_35;
    v24 = rf_object_resolve_handle(*((_DWORD *)v31 + 4));
    if ( v24 )
    {
      rf_model_handle_get_node_transform_adapter(*(_DWORD *)(v24 + 128), (int)v28, (int)v27, *((_DWORD *)v31 + 7));
      rf_particle_emitter_set_world_frame(*((_DWORD *)v31 + 3), v28, (float *)(*((_DWORD *)v31 + 3) + 20));
      rf_particle_emitter_process(*((_DWORD *)v31 + 3));
      if ( v31[12] <= 12.0 )
      {
        rf_model_handle_get_node_transform_adapter(*(_DWORD *)(v24 + 128), (int)rhs, (int)v27, *((_DWORD *)v31 + 5));
        rf_model_handle_get_node_transform_adapter(*(_DWORD *)(v24 + 128), (int)lhs, (int)v27, *((_DWORD *)v31 + 6));
        rf_model_handle_get_node_transform_adapter(*(_DWORD *)(v24 + 128), (int)v23, (int)v27, *((_DWORD *)v31 + 8));
        v0 = rf_vector_subtract(lhs, out_vector, rhs);
        rf_vector_copy(destination, copy_result, v0);
        rf_vector_normalize_reciprocal_sqrt(destination);
        scalar = rf_vector_distance(rhs, lhs);
        v1 = rf_vector_multiply_scalar(destination, scaled_result, scalar);
        v2 = rf_vector_multiply_scalar(v1, v12, 0.5);
        v3 = rf_vector_add(rhs, sum_result, v2);
        rf_vector_copy(v26, v10, v3);
        rf_particle_emitter_set_world_frame(*(_DWORD *)v31, v26, (float *)(*(_DWORD *)v31 + 20));
        rf_particle_emitter_process(*(_DWORD *)v31);
        rf_particle_emitter_set_world_frame(*((_DWORD *)v31 + 1), v28, (float *)(*((_DWORD *)v31 + 1) + 20));
        rf_particle_emitter_process(*((_DWORD *)v31 + 1));
        rf_particle_emitter_set_world_frame(*((_DWORD *)v31 + 2), v23, (float *)(*((_DWORD *)v31 + 2) + 20));
        rf_particle_emitter_process(*((_DWORD *)v31 + 2));
        if ( rf_replicator_has_elapsed(&unk_6E6710) )
        {
          rf_vector3_copy_return_destination(v20, v28);
          rf_vector_rotate_by_matrix3(v20, (float *)(v24 + 72));
          rf_vector_accumulate(v20, (float *)(v24 + 60));
          for ( i = (float *)unk_68211C; i != (float *)&unk_681E90; i = *((float **)i + 163) )
          {
            if ( i != (float *)v24
              && !rf_object_is_use_vehicle(i)
              && !rf_entity_is_dead((int)i)
              && !rf_object_has_respawn_inactive_flag((int)i)
              && !rf_entity_has_attached_use_vehicle((int)i)
              && rf_vector_distance_squared(i + 15, v20) <= 4.0 )
            {
              *((_DWORD *)i + 517) |= 0x2000u;
              v4 = *((_DWORD *)i + 165);
              v18 = *(float *)(v4 + 68) / rf_random_float_range(5.0, 8.0);
              v8 = v18 / 4.0;
              rf_damage_dispatch(
                *((_DWORD *)i + 11),
                v8,
                *((_DWORD *)v31 + 4),
                rf_weapon_id_flamethrower,
                4,
                0,
                *(_DWORD *)(v24 + 32),
                0);
            }
          }
        }
      }
      rf_positioned_voice_update(*((_DWORD *)v31 + 9), (float *)(v24 + 60), v24 + 324, v31[10]);
      if ( *((_BYTE *)v31 + 44) )
      {
        v31[12] = v31[12] + rf_frame_delta_seconds;
        sub_43F840(v31);
      }
      else if ( !rf_entity_is_dead(v24) )
      {
        v5 = *(_DWORD *)(v24 + 660);
        v16 = *(float *)(v5 + 68) / rf_random_float_range(5.0, 8.0);
        v7 = v16 * rf_frame_delta_seconds;
        rf_damage_dispatch(*(_DWORD *)(v24 + 44), v7, -1, -1, 4, 0, -1, 0);
        v17 = rand() % 3;
        if ( v17 )
        {
          if ( v17 == 1 )
          {
            *(_DWORD *)(v24 + 2084) = 14;
          }
          else if ( v17 == 2 )
          {
            *(_DWORD *)(v24 + 2084) = 15;
          }
        }
        else
        {
          *(_DWORD *)(v24 + 2084) = 5;
        }
      }
LABEL_35:
      v31 = v21;
    }
    else
    {
      rf_burn_effect_release_record(v31, 0);
    }
  }
  if ( rf_replicator_has_elapsed(&unk_6E6710) )
    return rf_replicator_arm_milliseconds(&unk_6E6710, 225);
  result = rf_replicator_is_armed(&unk_6E6710);
  if ( !result )
    return rf_replicator_arm_milliseconds(&unk_6E6710, 225);
  return result;
}

