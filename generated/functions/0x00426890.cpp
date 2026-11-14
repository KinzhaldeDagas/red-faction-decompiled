// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00426890 rf_entity_update_shield_ai_vfx_and_runtime_markers
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl required ENTITY, void. Respawn-inactive predicate EXACT AL1 OR full handle DWORD+44==0 exits before any own stores; other byte
// values/negative handles are not rejected. If shield UID+5200!=-1, COMMON type4 clutter lookup is attempted; resolved shield reactivates iff selected weapon+676==global911C80,
// otherwise hides/inactivates. Unresolved stored UID is retained, not recreated. Only UID==-1 AND weapon match looks up literal riot_shield, creates clutter(classIndex,emptyName,raw
// owner full handle,COMMON position,COMMON matrix,0), and stores returned object handle iff nonNULL; no class-index guard. Afterwards zeros vectors entity+2160 then+2184. Vector+2208
// is preserved ONLY if437F00 returns any nonzero AND entity DWORD+424 mask00400000 set; otherwise zeros it. Calls426E20; ANY nonzero admits profiled AI update(entity+672), then
// subsequent fields are freshly read.  NonNULL model+128 with descriptor kind EXACT2 enters VFX gate. Start allow1; NULL cached room makes0. NonNULL room BYTE+352==0 plus entity
// DWORD+2068 high bit CLEAR plus entity state DWORD+1312 in{1,2,13} makes0. Only current allow==1 AND high bit CLEAR AND signed class DWORD+5048>2 applies distance cull. Splitscreen
// ANY nonzero uses Euclidean FLOAT32 distances to camera COMMON positions from entry0 unconditionally and entry1 only if SIGNED local count>1; absent second uses FLOAT9999.900390625.
// Chooses second distance on equality OR UNORDERED, first only ordered second>first. Nonsplit calls581710(position) and rounds returnedST0 FLOAT32. Only ordered selected
// distance>DOUBLE45 clears allow; equality/NaN preserves it. Dead predicate EXACT AL1 then forces allow1 despite prior room/distance rejection. Any nonzero allow invokes VFX
// update(model,frameDeltaSeconds,0,COMMON position,COMMON matrix,1). No model-kind bypass from death.  Independently, runtime flags DWORD+2064 mask00020000 builds side
// direction=COMMON matrix first row CROSS(0,1,0), then target=COMMON position+1000*direction with native rounded vector intermediates. Calls410920(entity,target); ONLY ordered
// ST0<DOUBLE0.01 clears mask00020000; equality/NaN leaves it. No distance-cull early return bypasses this steering step.  Finally re-reads model; NULL exits.421980 ANY nonzero: get
// model runtime, and if nonNULL call426EF0(entity,runtime,1), DISCARD ST0, then OR ENTITY flags DWORD+2064 highbit80000000. False predicate: get runtime; require both class
// indices+5080/+5084 !=-1 and at least one selected BYTE[runtime+5052+48*index]==EXACT1. No other index bounds. If entity runtime highbit was set, zero FLOAT+5220 then clear highbit
// BEFORE426EF0(entity,runtime,0). Only ordered returnedST0==0 clears BOTH selected marker bytes and zeros+5220 again; nonzero/NaN retains markers. No uniform result, transaction,
// stale-handle repair, own pointer/class/camera/capacity/finite validation or rollback.
void __cdecl rf_entity_update_shield_ai_vfx_and_runtime_markers(int entity)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float scaled_result[3]; // [esp+14h] [ebp-8Ch] BYREF
  float copy_result[3]; // [esp+20h] [ebp-80h] BYREF
  float v7[3]; // [esp+2Ch] [ebp-74h] BYREF
  float v8[3]; // [esp+38h] [ebp-68h] BYREF
  float out_vector[3]; // [esp+44h] [ebp-5Ch] BYREF
  int v10; // [esp+50h] [ebp-50h]
  int runtime_pointer; // [esp+54h] [ebp-4Ch]
  float v12[3]; // [esp+58h] [ebp-48h] BYREF
  float sum_result[3]; // [esp+64h] [ebp-3Ch] BYREF
  float destination[3]; // [esp+70h] [ebp-30h] BYREF
  float v15; // [esp+7Ch] [ebp-24h]
  float v16; // [esp+80h] [ebp-20h]
  float v17; // [esp+84h] [ebp-1Ch]
  int first_dword; // [esp+88h] [ebp-18h]
  char v19; // [esp+8Fh] [ebp-11h]
  int kind; // [esp+90h] [ebp-10h]
  _DWORD *v21; // [esp+94h] [ebp-Ch]
  int index_by_name; // [esp+98h] [ebp-8h]
  _DWORD *v23; // [esp+9Ch] [ebp-4h]

  if ( !rf_object_has_respawn_inactive_flag(entity) && *(_DWORD *)(entity + 44) )
  {
    if ( *(_DWORD *)(entity + 5200) == -1 )
    {
      if ( *(_DWORD *)(entity + 676) == unk_911C80 )
      {
        index_by_name = rf_clutter_class_find_index_by_name("riot_shield");
        v21 = rf_clutter_runtime_create(
                index_by_name,
                (char *)&byte_631A9F,
                *(_DWORD *)(entity + 44),
                (float *)(entity + 60),
                (float *)(entity + 72),
                0);
        if ( v21 )
          *(_DWORD *)(entity + 5200) = v21[11];
      }
    }
    else
    {
      v23 = (_DWORD *)rf_clutter_find_by_uid(*(_DWORD *)(entity + 5200));
      if ( v23 )
      {
        if ( *(_DWORD *)(entity + 676) == unk_911C80 )
          rf_object_reactivate_from_respawn(v23);
        else
          rf_object_mark_hidden_inactive((int)v23);
      }
    }
    rf_vector3_zero_return_destination((float *)(entity + 2160));
    rf_vector3_zero_return_destination((float *)(entity + 2184));
    if ( !rf_entity_uses_fall_or_airborne_vehicle_motion(entity) || (*(_DWORD *)(entity + 424) & 0x400000) == 0 )
      rf_vector3_zero_return_destination((float *)(entity + 2208));
    if ( rf_entity_ai_update_admit(entity) )
      rf_ai_update_profiled_if_not_pending_delete((int *)(entity + 672));
    if ( *(_DWORD *)(entity + 128) )
    {
      kind = rf_model_descriptor_get_kind(*(_DWORD *)(entity + 128));
      if ( kind == 2 )
      {
        v19 = 1;
        first_dword = rf_receiver_get_first_dword((void *)entity);
        if ( first_dword )
        {
          if ( !*(_BYTE *)(first_dword + 352)
            && *(int *)(entity + 2068) >= 0
            && (*(_DWORD *)(entity + 1312) == 2 || *(_DWORD *)(entity + 1312) == 1 || *(_DWORD *)(entity + 1312) == 13) )
          {
            v19 = 0;
          }
        }
        else
        {
          v19 = 0;
        }
        if ( v19 == 1 && *(int *)(entity + 2068) >= 0 && *(int *)(*(_DWORD *)(entity + 660) + 5048) > 2 )
        {
          if ( rf_splitscreen_runtime_active )
          {
            v16 = 9999.9004;
            v15 = 9999.9004;
            v1 = rf_vector_subtract(
                   (const float *)(**(_DWORD **)(rf_local_player_entries[0] + 196) + 60),
                   out_vector,
                   (const float *)(entity + 60));
            v16 = rf_vector3_length(v1);
            if ( rf_local_player_entry_count > 1 )
            {
              v2 = rf_vector_subtract(
                     (const float *)(**(_DWORD **)(unk_87C5B4 + 196) + 60),
                     v8,
                     (const float *)(entity + 60));
              v15 = rf_vector3_length(v2);
            }
            if ( v15 <= (double)v16 )
              v17 = v15;
            else
              v17 = v16;
          }
          else
          {
            v17 = rf_renderer_lod_distance_scaled((const float *)(entity + 60));
          }
          if ( v17 > 45.0 )
            v19 = 0;
        }
        if ( rf_entity_is_dead(entity) )
          v19 = 1;
        if ( v19 )
          rf_vfx_update_instance(*(int **)(entity + 128), rf_frame_delta_seconds, 0, entity + 60, entity + 72, 1);
      }
    }
    if ( (*(_DWORD *)(entity + 2064) & 0x20000) != 0 )
    {
      rf_vector3_default_construct_noop(destination);
      rf_vector3_default_construct_noop(v12);
      rf_vector3_set_components_thiscall(v12, 0.0, 1.0, 0.0);
      v3 = rf_vector_cross((float *)(entity + 72), v7, v12);
      rf_vector_copy(destination, copy_result, v3);
      v4 = rf_vector_multiply_scalar(destination, scaled_result, 1000.0);
      rf_vector_add((const float *)(entity + 60), sum_result, v4);
      if ( sub_410920(entity, sum_result) < 0.01 )
        *(_DWORD *)(entity + 2064) &= ~0x20000u;
    }
    if ( *(_DWORD *)(entity + 128) )
    {
      if ( rf_entity_weapon_pose_update_admitted(entity) )
      {
        runtime_pointer = rf_model_handle_get_runtime_pointer(*(int **)(entity + 128));
        if ( runtime_pointer )
        {
          rf_entity_update_two_node_rotation_overrides(entity, runtime_pointer, 1);
          *(_DWORD *)(entity + 2064) |= 0x80000000;
        }
      }
      else
      {
        v10 = rf_model_handle_get_runtime_pointer(*(int **)(entity + 128));
        if ( v10
          && *(_DWORD *)(*(_DWORD *)(entity + 660) + 5080) != -1
          && *(_DWORD *)(*(_DWORD *)(entity + 660) + 5084) != -1
          && (*(_BYTE *)(v10 + 48 * *(_DWORD *)(*(_DWORD *)(entity + 660) + 5080) + 5052) == 1
           || *(_BYTE *)(v10 + 48 * *(_DWORD *)(*(_DWORD *)(entity + 660) + 5084) + 5052) == 1) )
        {
          if ( *(int *)(entity + 2064) < 0 )
          {
            *(float *)(entity + 5220) = 0.0;
            *(_DWORD *)(entity + 2064) &= ~0x80000000;
          }
          if ( rf_entity_update_two_node_rotation_overrides(entity, v10, 0) == 0.0 )
          {
            *(_BYTE *)(v10 + 48 * *(_DWORD *)(*(_DWORD *)(entity + 660) + 5080) + 5052) = 0;
            *(_BYTE *)(v10 + 48 * *(_DWORD *)(*(_DWORD *)(entity + 660) + 5084) + 5052) = 0;
            *(float *)(entity + 5220) = 0.0;
          }
        }
      }
    }
  }
}

