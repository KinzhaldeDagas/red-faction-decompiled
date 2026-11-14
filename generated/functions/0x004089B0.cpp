// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004089B0 rf_ai_update_retained_target_route_policy
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block. Replacement predicate404AC0 EXACT1 invokes404740 scan before resolving COMMON target+704
// into cached old-target pointer. Missing ->422270(owner handle,primary index+4)==EXACT1 stops firing, then40A2A0(block); no direct raw target clear. Found ->resolve same handle as
// ENTITY. Attached-use-vehicle predicate EXACT1 and resolved attached owner ENTITY nonnull with turret predicate AL0 DIRECTLY writes original target entity+512 handle to block+704,
// bypassing guarded setter. Cached common target and entity pointers are NOT replaced/re-resolved for following classification/probe operations. If old entity is use-vehicle OR
// turret, runtime-enabled/resolved-attachment(oldEntity,-1) AL0 and its numeric mode+1312==1 ->40BA80(block,-1) and exit. Otherwise4025D0(block,CACHED OLD COMMON target), then
// delta=float32(global pause-gated seconds6FC428-block FLOAT+664). Owner class FLOAT+1816 ordered<delta AND runtime BYTE0 AND splitscreen BYTE0 ->guarded clear-1 and exit; equality
// or unordered retains. Then408800(block) re-resolves CURRENT block handle, potentially redirected earlier. Unless secondary11: approach predicate nonzero plus secondary!=1 and+560
// elapsed EXACT1 ->no-write local ctor,401000(block,out) ignored result, route_build(owner handle,out). Builder EXACT AL1 writes secondary1 then OR flags+1328 mask8; all other AL
// reset route+744 then arm+560 inclusive500..1000ms. Approach false with secondary1 instead arms+564 inclusive500..1000, resets route, writes secondary2. Independently+564 elapsed
// EXACT1 dispatches4083A0 for secondary11 or408090 for secondary2, re-reading state. Then native call4085A0(block,extra CACHED OLD target+60), cleans8; extra is not consumed
// by4085A0. Finally current primary mode!=7 invokes401670(block) then407D90(block). No nearest-target or role gate of its own, no second target validation after callbacks; EAX/AL
// incidental.
void __cdecl rf_ai_update_retained_target_route_policy(int a1)
{
  float v1[3]; // [esp+4h] [ebp-20h] BYREF
  int v2; // [esp+10h] [ebp-14h]
  float v3; // [esp+14h] [ebp-10h]
  bool v4; // [esp+1Bh] [ebp-9h]
  int v5; // [esp+1Ch] [ebp-8h]
  _DWORD *v6; // [esp+20h] [ebp-4h]

  if ( rf_ai_should_seek_replacement_target((int *)a1) )
    rf_ai_scan_and_commit_weighted_target((int *)a1);
  v5 = rf_object_resolve_handle(*(_DWORD *)(a1 + 704));
  if ( v5 )
  {
    v6 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 704));
    if ( rf_entity_has_attached_use_vehicle((int)v6) )
    {
      v2 = rf_entity_resolve_handle(v6[128]);
      if ( v2 )
      {
        if ( !rf_entity_has_turret_flag(v2) )
          *(_DWORD *)(a1 + 704) = v6[128];
      }
    }
    if ( (rf_object_is_use_vehicle(v6) || rf_entity_has_turret_flag((int)v6))
      && !rf_entity_runtime_enabled_or_resolved_attachment((int)v6, -1)
      && v6[328] == 1
      || (rf_ai_refresh_target_collision_and_corridor_probes((int *)a1, v5),
          v3 = *(float *)&dword_6FC428 - *(float *)(a1 + 664),
          *(float *)(*(_DWORD *)(*(_DWORD *)a1 + 660) + 1816) < (double)v3)
      && !rf_multiplayer_runtime_mode
      && !rf_splitscreen_runtime_active )
    {
      sub_40BA80((int *)a1, -1);
    }
    else
    {
      v4 = rf_ai_target_needs_route_approach((int *)a1);
      if ( *(_DWORD *)(a1 + 692) != 11 )
      {
        if ( v4 )
        {
          if ( *(_DWORD *)(a1 + 692) != 1 && rf_replicator_has_elapsed((int *)(a1 + 560)) )
          {
            rf_vector3_default_construct_noop(v1);
            rf_ai_copy_route_target_position(a1, v1);
            if ( rf_ai_route_build(*(_DWORD *)(*(_DWORD *)a1 + 44), (int)v1) == 1 )
            {
              rf_ai_secondary_state_write(a1, 1);
              *(_DWORD *)(a1 + 1328) |= 8u;
            }
            else
            {
              rf_ai_route_reset(a1 + 744);
              rf_timestamp_arm_random_inclusive_milliseconds((int *)(a1 + 560), 500, 1000);
            }
          }
        }
        else if ( *(_DWORD *)(a1 + 692) == 1 )
        {
          rf_timestamp_arm_random_inclusive_milliseconds((int *)(a1 + 564), 500, 1000);
          rf_ai_route_reset(a1 + 744);
          rf_ai_secondary_state_write(a1, 2);
        }
      }
      if ( rf_replicator_has_elapsed((int *)(a1 + 564)) )
      {
        if ( *(_DWORD *)(a1 + 692) == 11 )
        {
          rf_ai_select_secondary2_with_timing((int *)a1);
        }
        else if ( *(_DWORD *)(a1 + 692) == 2 )
        {
          rf_ai_select_secondary11_after_reload_or_route_retry((_DWORD *)a1);
        }
      }
      rf_ai_face_target_and_advance_route((int *)a1);
      if ( *(_DWORD *)(a1 + 640) != 7 )
      {
        rf_ai_dispatch_selected_primary_weapon_action((int *)a1);
        rf_ai_secondary_weapon_action_dispatch((int *)a1);
      }
    }
  }
  else
  {
    if ( rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(*(_DWORD *)a1 + 44), *(_DWORD *)(a1 + 4)) )
      rf_entity_stop_weapon_firing(*(_DWORD *)(*(_DWORD *)a1 + 44), *(_DWORD *)(a1 + 4));
    sub_40A2A0((int *)a1);
  }
}

