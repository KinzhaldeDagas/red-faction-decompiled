// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00401670 rf_ai_dispatch_selected_primary_weapon_action
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): One required AI-block pointer, owner entity at+0. Resolves target full handle+704 as ENTITY ON ENTRY; this
// captured pointer is used by weapon choice/clearance, while401B60 later re-resolves current target as COMMON object. Before ANY global firing/ready/reload gate, if class(+660)
// optional weapon DWORD+144!=-1 and captured entity target exists, read FLOAT912514+1360*optionalIndex, square and roundfloat32; compare with float32 squared COMMON-position
// distance. Ordered limitSquared>distanceSquared selects optional class weapon+144; distanceSquared>=limitSquared OR UNORDERED selects DEFAULT class weapon+136. Only on actual
// change: both branches stop old selected firing, store new AI primary+4 and call438DE0(owner,newIndex). Optional branch additionally arms block+1188 at0ms, arms+536 at0ms, writes
// DWORD+608=0 BEFORE storing new primary; default branch does not reset these fields. No optional/primary index upper bound or lower bound other than optional!=-1. Then global
// BYTE661010 must be nonzero, ready predicate AL nonzero; flinch-override EXACT AL1, reload EXACT1, or unholster-pending EXACT1 prevents action. Pending case calls40B900 unholster
// starter before returning0. Block+1188 deadline elapsed any nonzero required; BYTE+670==EXACT1 returns0 before launcher checks/readiness. Other nonzero byte values do not veto.
// Current selected primary equal shoulder-cannon or rocket-launcher global IDs plus captured entity target enters launcher clearance. Read scalar FLOAT912208+1360*primary; float32
// squared COMMON distance ordered<UNROUNDED x87(scalar*scalar*DOUBLE0.25) invokes default-primary helper438DF0 and returnsAL0 immediately. Equality/NaN skip this fallback. Otherwise
// compute muzzle transform(owner,primary,&rhs,&matrix), IGNORE result; target point helper uses captured entity retained point/common position; normalize(point-rhs),
// endpoint=rhs+scalar*direction. Seven-slot collision(rhs,endpoint,FLOAT1.2999999523162842,mask0x21,owner,captured target,NULL)==EXACT AL1 returns0; other AL continues.
// Independently5119F0(current primary) any nonzero plus captured entity target: float32 squared COMMON distance ordered<DOUBLE16 invokes default-primary helper but DOES NOT exit, so
// readiness/action can use the newly selected default in this same call. Calls401B60(&stopRequestByte,block); that helper initializes byte0 and returns separate readiness AL.
// Readiness EXACT AL1 calls431FD0(owner,0,0,NULL,0,0), six stack arguments, IGNORING action result. Afterwards any nonzero runtime/splitscreen enables403030(owner); nonzero AL there
// returnsEXPLICIT AL1. This is the ONLY return1 path, so successful single-player weapon action still returns0 and failed431FD0 may still permit route-request result1. Otherwise if
// stopRequestByte==EXACT1:422270(owner handle,current primary) any nonzero AND deadline+556 disarmed arms same deadline with0ms when AI flags+1328 mask0x8000 set, else
// rand()%1000+1000ms. Independently, stopRequestByte1 and+556 elapsed EXACT1 stops current primary firing; no reset/disarm after stop, so expired stop deadline persists.
// Stop-request0 does not test or cancel an already armed stop deadline. All other exits explicitly AL0. No own global authority gate or uniform firing-success return.
char __cdecl rf_ai_dispatch_selected_primary_weapon_action(int *a1)
{
  float *v2; // eax
  int v3; // eax
  float scaled_result[3]; // [esp+14h] [ebp-7Ch] BYREF
  float v5; // [esp+20h] [ebp-70h]
  float v6; // [esp+24h] [ebp-6Ch]
  float lhs[3]; // [esp+28h] [ebp-68h] BYREF
  char v8[36]; // [esp+34h] [ebp-5Ch] BYREF
  float out_vector[3]; // [esp+58h] [ebp-38h] BYREF
  float scalar; // [esp+64h] [ebp-2Ch]
  float rhs[3]; // [esp+68h] [ebp-28h] BYREF
  float sum_result[3]; // [esp+74h] [ebp-1Ch] BYREF
  float v13; // [esp+80h] [ebp-10h]
  float v14; // [esp+84h] [ebp-Ch]
  char v15; // [esp+8Bh] [ebp-5h] BYREF
  int v16; // [esp+8Ch] [ebp-4h]

  v16 = rf_entity_resolve_handle(a1[176]);
  if ( *(_DWORD *)(*(_DWORD *)(*a1 + 660) + 144) != -1 && v16 )
  {
    v14 = *((float *)&unk_912514 + 340 * *(_DWORD *)(*(_DWORD *)(*a1 + 660) + 144));
    v14 = v14 * v14;
    v13 = rf_vector_distance_squared((const float *)(*a1 + 60), (const float *)(v16 + 60));
    if ( v14 <= (double)v13 )
    {
      if ( a1[1] != *(_DWORD *)(*(_DWORD *)(*a1 + 660) + 136) )
      {
        rf_entity_stop_weapon_firing(*(_DWORD *)(*a1 + 44), a1[1]);
        a1[1] = *(_DWORD *)(*(_DWORD *)(*a1 + 660) + 136);
        rf_entity_restore_action_tables_and_apply_weapon_overrides(*a1, a1[1]);
      }
    }
    else if ( a1[1] != *(_DWORD *)(*(_DWORD *)(*a1 + 660) + 144) )
    {
      rf_entity_stop_weapon_firing(*(_DWORD *)(*a1 + 44), a1[1]);
      rf_replicator_arm_milliseconds(a1 + 297, 0);
      rf_replicator_arm_milliseconds(a1 + 134, 0);
      a1[152] = 0;
      a1[1] = *(_DWORD *)(*(_DWORD *)(*a1 + 660) + 144);
      rf_entity_restore_action_tables_and_apply_weapon_overrides(*a1, a1[1]);
    }
  }
  if ( !byte_661010 )
    return 0;
  if ( !rf_ai_is_ready_flag_set((int)a1) )
    return 0;
  if ( rf_character_update_damage_flinch_override(*a1) == 1 )
    return 0;
  if ( rf_entity_reload_in_progress(*a1) )
    return 0;
  if ( rf_ai_unholster_pending_flag_set((int)a1) )
  {
    rf_ai_start_pending_unholster_action(a1);
    return 0;
  }
  if ( !rf_replicator_has_elapsed(a1 + 297) )
    return 0;
  if ( *((_BYTE *)a1 + 670) == 1 )
    return 0;
  if ( a1[1] != rf_weapon_id_shoulder_cannon && a1[1] != rf_weapon_id_rocket_launcher || !v16 )
    goto LABEL_50;
  scalar = *((float *)&unk_912208 + 340 * a1[1]);
  v6 = rf_vector_distance_squared((const float *)(*a1 + 60), (const float *)(v16 + 60));
  if ( v6 < scalar * scalar * 0.25 )
  {
    rf_ai_switch_to_default_primary_after_launcher_exhaustion(a1);
    return 0;
  }
  rf_vector3_default_construct_noop(rhs);
  rf_matrix3_construct(v8);
  rf_entity_compute_weapon_muzzle_transform((_DWORD *)*a1, a1[1], (int)rhs, (int)v8);
  rf_vector3_default_construct_noop(lhs);
  rf_object_copy_entity_vector7D4_or_position(v16, lhs);
  rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_normalize(out_vector);
  v2 = rf_vector_multiply_scalar(out_vector, scaled_result, scalar);
  rf_vector_add(rhs, sum_result, v2);
  if ( rf_segment_objects_or_world_hit_filtered_by_radius((int)rhs, (int)sum_result, 1.3, 33, *a1, v16, 0) == 1 )
    return 0;
LABEL_50:
  if ( sub_5119F0(a1[1]) )
  {
    if ( v16 )
    {
      v5 = rf_vector_distance_squared((const float *)(*a1 + 60), (const float *)(v16 + 60));
      if ( v5 < 16.0 )
        rf_ai_switch_to_default_primary_after_launcher_exhaustion(a1);
    }
  }
  if ( rf_ai_primary_weapon_ready_with_stop_request(&v15, a1) == 1 )
  {
    sub_431FD0(*a1, 0, 0, nullptr, 0, 0);
    if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
    {
      if ( rf_ai_queue_close_target_route_request(*a1) )
        return 1;
    }
  }
  if ( v15 == 1 )
  {
    if ( rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(*a1 + 44), a1[1]) && !rf_replicator_is_armed(a1 + 139) )
    {
      if ( (a1[332] & 0x8000) != 0 )
      {
        rf_replicator_arm_milliseconds(a1 + 139, 0);
      }
      else
      {
        v3 = rand();
        rf_replicator_arm_milliseconds(a1 + 139, v3 % 1000 + 1000);
      }
    }
    if ( rf_replicator_has_elapsed(a1 + 139) )
      rf_entity_stop_weapon_firing(*(_DWORD *)(*a1 + 44), a1[1]);
  }
  return 0;
}

