// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004085A0 rf_ai_face_target_and_advance_route
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One consumed cdecl AI-block pointer; some callers push an ignored extra target-position pointer. Any-nonzero
// owner-dead AL exits; resolve COMMON retained target handle+704, miss exits. Build facing point: source current descriptor POINTER equals445740(7) or445740(9) ->target COMMON
// position+60, else4010E0(block,target,out). Registry lookup may fall back to slot0; do not equate pointer checks with guaranteed mode indices. Calls410920(owner,point), discards
// returnedST0 BEFORE DWORD block+1184==2 suppresses further route work. Secondary1: only when route DWORD+744==0 and deadline+560 elapsed EXACT1 tries route_build(owner handle,target
// COMMON+60). AL0 arms+5601000ms and returns without explicit route-reset; otherwise, or when attempt gates fail, calls40ECE0(route=block+744,extra1), cleans8bytes. Secondary3:
// compare source current descriptor pointer to445740(1); if equal and secondary still3 flatten copied target.Y to owner common.Y. Compute Euclidean distance roundedfloat32 and
// maximum attack range4098B0 roundedfloat32. Only ordered distance>range*DOUBLE0.6000000238418579 proceeds. If+560 elapsed EXACT1 tries route_build with UNMODIFIED target COMMON
// position, AL0 arms1000ms and returns; otherwise calls route_update(route,extra1). Secondary11 directly calls route_update(route,extra1); other secondary states do no further route
// work. No route update inside near/equal/unordered secondary3 threshold, no own rate rearm on successful builder, role or inactive-owner gate.
void __cdecl rf_ai_face_target_and_advance_route(int *a1)
{
  int v1; // esi
  int v2; // esi
  int v3; // esi
  float copy_result[3]; // [esp+4h] [ebp-34h] BYREF
  float v5[3]; // [esp+10h] [ebp-28h] BYREF
  float v6; // [esp+1Ch] [ebp-1Ch]
  float v7; // [esp+20h] [ebp-18h]
  bool v8; // [esp+27h] [ebp-11h]
  float destination[3]; // [esp+28h] [ebp-10h] BYREF
  int v10; // [esp+34h] [ebp-4h]

  if ( !rf_entity_is_dead(*a1) )
  {
    v10 = rf_object_resolve_handle(a1[176]);
    if ( v10 )
    {
      rf_vector3_default_construct_noop(destination);
      v1 = *a1;
      if ( *(char **)(v1 + 2136) == sub_445740(7u) || (v2 = *a1, *(char **)(v2 + 2136) == sub_445740(9u)) )
        rf_vector_copy(destination, copy_result, (const float *)(v10 + 60));
      else
        rf_ai_copy_target_point_for_current_movement(a1, v10, destination);
      sub_410920(*a1, destination);
      if ( a1[296] != 2 )
      {
        if ( a1[173] == 1 )
        {
          if ( !a1[186] && rf_replicator_has_elapsed(a1 + 140) && !rf_ai_route_build(*(_DWORD *)(*a1 + 44), v10 + 60) )
          {
LABEL_12:
            rf_replicator_arm_milliseconds(a1 + 140, 1000);
            return;
          }
LABEL_24:
          rf_ai_route_update((int)(a1 + 186));
          return;
        }
        if ( a1[173] != 3 )
        {
          if ( a1[173] != 11 )
            return;
          goto LABEL_24;
        }
        v3 = *a1;
        v8 = *(_DWORD *)(v3 + 2136) == (_DWORD)sub_445740(1u);
        rf_vector3_copy_return_destination(v5, (float *)(v10 + 60));
        if ( v8 && a1[173] == 3 )
          v5[1] = *(float *)(*a1 + 64);
        v6 = rf_vector_distance(v5, (const float *)(*a1 + 60));
        v7 = rf_ai_resolve_maximum_attack_range(a1);
        if ( v6 > v7 * 0.6000000238418579 )
        {
          if ( rf_replicator_has_elapsed(a1 + 140) && !rf_ai_route_build(*(_DWORD *)(*a1 + 44), v10 + 60) )
            goto LABEL_12;
          rf_ai_route_update((int)(a1 + 186));
        }
      }
    }
  }
}

