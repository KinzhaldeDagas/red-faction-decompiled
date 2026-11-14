// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00406B20 rf_ai_mode5_approach_and_associate_target
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, mode5 secondary5 handler. Resolve COMMON target+704; missing resets route+744 and selects
// secondary4 without clearing flags/reservation. Valid ->4025D0 probes; BYTE+668!=EXACT1 only route-update(route+744,extra1) and exits. Exact1: copy target COMMON position and
// increase Y by DOUBLE1.100000023841858 with float32 store; distance from owner COMMON roundsfloat32. Ordered distance>4 faces raised target directly. Ordered distance<=4 OR
// UNORDERED instead faces raised point+100*owner COMMON forward row+96 with Y restored to raised-point Y. Both410920 results discarded. If434C10(owner) AL0, scalar is1 on ordered
// distance>4; otherwise float32(distance/4), including NaN; invoke clamp[-1,1], normalize/accumulate raised-target-minus-owner vector through40B7B0. Local attachment-ready and
// action-finished bytes start0. Ordered distance<0.5 AND AI flags+1328 mask0x10 clear: signed animation record owner+3204<0 sets attachment-ready1 WITHOUT setting mask/timer;
// otherwise request body action35(1.0,0,1), ignores result, sets mask0x10 and arms+600 for5500ms. Mask0x10 set independently tests deadline+600 elapsed EXACT1 (sets attachment-ready
// and resets timer), and active-action35 AL0 (sets action-finished). Attachment-ready1 AND434C10 AL0 dereferences FIRST association slot in owner registry+2252 without count/null
// check; calls434200 with ECX=owner, stack(target handle,slot DWORD0), ignores result, then ORs TARGET common mask0x100. Action-finished1 calls406E70(block); nonzero result exits.
// ZERO builds route(owner handle,block+1168); nonzero AL selects secondary6 and clears mask0x10, zero requests primary mode1(-1,-1) leaving this mask unchanged here. Missing
// animation by itself does not set action-finished or trigger nearest-event route branch. Native zeroed-ECX/JNZ self-loops on error paths are never taken; no wait/spin is performed.
void __cdecl rf_ai_mode5_approach_and_associate_target(int *a1)
{
  float *v1; // eax
  int **v2; // eax
  float scaled_result[3]; // [esp+Ch] [ebp-44h] BYREF
  int v4; // [esp+18h] [ebp-38h]
  float out_vector[3]; // [esp+1Ch] [ebp-34h] BYREF
  int v6; // [esp+28h] [ebp-28h] BYREF
  float sum_result[3]; // [esp+2Ch] [ebp-24h] BYREF
  int v8; // [esp+38h] [ebp-18h]
  float lhs; // [esp+3Ch] [ebp-14h] BYREF
  float v10; // [esp+40h] [ebp-10h]
  char v11; // [esp+4Ah] [ebp-6h]
  char v12; // [esp+4Bh] [ebp-5h]
  int v13; // [esp+4Ch] [ebp-4h]

  v13 = rf_object_resolve_handle(a1[176]);
  if ( v13 )
  {
    rf_ai_refresh_target_collision_and_corridor_probes(a1, v13);
    if ( *((_BYTE *)a1 + 668) == 1 )
    {
      rf_vector3_copy_return_destination(&lhs, (float *)(v13 + 60));
      v10 = v10 + 1.100000023841858;
      *(float *)&v8 = rf_vector_distance((const float *)(*a1 + 60), &lhs);
      if ( *(float *)&v8 <= 4.0 )
      {
        v1 = rf_vector_multiply_scalar((const float *)(*a1 + 96), scaled_result, 100.0);
        rf_vector_add(&lhs, sum_result, v1);
        sum_result[1] = v10;
        sub_410920(*a1, sum_result);
      }
      else
      {
        sub_410920(*a1, &lhs);
      }
      if ( !rf_entity_any_attached_child_has_player_flag(*a1) )
      {
        v6 = v8;
        if ( *(float *)&v8 <= 4.0 )
          *(float *)&v6 = *(float *)&v8 / 4.0;
        else
          *(float *)&v6 = 1.0;
        rf_float_clamp_in_place((float *)&v6, -1.0, 1.0);
        rf_vector_subtract(&lhs, out_vector, (const float *)(*a1 + 60));
        rf_ai_accumulate_normalized_world_vector((int)a1, out_vector, *(float *)&v6);
      }
      v12 = 0;
      v11 = 0;
      if ( *(float *)&v8 < 0.5 && (a1[332] & 0x10) == 0 )
      {
        v4 = *(_DWORD *)(*a1 + 3204);
        if ( v4 < 0 )
        {
          v12 = 1;
        }
        else
        {
          rf_entity_request_body_action(*a1, 0x23u, 1.0, 0, 1);
          a1[332] |= 0x10u;
          rf_replicator_arm_milliseconds(a1 + 150, 5500);
        }
      }
      if ( (a1[332] & 0x10) != 0 )
      {
        if ( rf_replicator_has_elapsed(a1 + 150) )
        {
          v12 = 1;
          rf_replicator_reset(a1 + 150);
        }
        if ( !rf_entity_body_action_is_active(*a1, 0x23u) )
          v11 = 1;
      }
      if ( v12 == 1 && !rf_entity_any_attached_child_has_player_flag(*a1) )
      {
        v2 = (int **)sub_552200((_DWORD *)(*a1 + 2252), 0);
        rf_entity_associate_child_with_last_slot_key(*a1, *(_DWORD *)(v13 + 44), **v2);
        *(_DWORD *)(v13 + 124) |= 0x100u;
      }
      if ( v11 == 1 && !rf_ai_find_nearest_type27_event_position(a1) )
      {
        if ( rf_ai_route_build(*(_DWORD *)(*a1 + 44), (int)(a1 + 292)) )
        {
          rf_ai_secondary_state_write((int)a1, 6);
          a1[332] &= ~0x10u;
        }
        else
        {
          rf_ai_numeric_mode_write(a1, 1, -1, -1);
        }
      }
    }
    else
    {
      rf_ai_route_update((int)(a1 + 186));
    }
  }
  else
  {
    rf_ai_route_reset((int)(a1 + 186));
    rf_ai_secondary_state_write((int)a1, 4);
  }
}

