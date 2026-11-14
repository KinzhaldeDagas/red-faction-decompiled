// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00407230 rf_ai_numeric_mode3_update
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, owner entity at+0. Dead predicate EXACT AL1 or scripted-action-remaining EXACT1 exits.
// Class flags724 mask0x800 predicate EXACT1 delegates4089B0(block) and exits. Replacement predicate404AC0 EXACT1: if primary-flag20-without-secondary EXACT1, call40FD80(owner
// COMMON+60,FLOAT block+1312,FLOAT+1316,boolean,block+1020,block+1024,0) with seven stack slots; boolean is0 only when437F60(owner) and current movement index4/7 predicate are both
// nonzero. Write secondary0, then404740 weighted scan (scan occurs even without primary-flag predicate). Resolve retained target+704 as COMMON pointer; missing ->422270(owner
// handle,primary index) EXACT1 optionally stops firing, then any nonzero runtime/splitscreen calls402FD0(block,1), otherwise40A2A0(block), exit. Independently resolve target as
// ENTITY. Attached-use-vehicle EXACT1 ->resolve entity attachment+512; if parent ENTITY exists and turret predicate AL0, DIRECTLY overwrite block target+704 with attachment full
// handle. This bypasses guarded target setter and DOES NOT replace captured old common/entity pointers used later. If old target is use-vehicle or turret,
// runtime-enabled/resolved-attachment(old,-1) AL0 and old mode+1312==1 ->guarded target clear-1 and exit. Snapshot visibility as true only when BYTE+668 or+669==EXACT1, THEN4025D0
// probes(block,captured COMMON target). Primary-flag20 EXACT1 plus old target turret/attached-turret/use-vehicle: if postprobe byte668/669 EXACT1,40AC80(block,old entity
// handle,5.0f); EXIT this whole handler regardless of visibility. Other paths: postprobe both bytesZERO with preprobe snapshot true arms block+568 inclusive2000..5000ms. Compute
// float32(global seconds6FC428-block FLOAT+664); class FLOAT+1816 ordered strictly less than that delta clears target and exits ONLY when both runtime/splitscreen bytes0. Then save
// AL of408800(block) as range/route policy; later helper mutations do not refresh this saved result. In runtime/splitscreen: flags+1328 mask0x02000000 ->40ECE0(route+744,extra0); any
// EAX!=-1 exits; -1 clears mask and continues WITHOUT402D70 in same call. Otherwise402D70(block,0) nonzero AL exits. If saved policy nonzero, current mode!=7,(secondary!=1 OR route
// DWORD+744==0),deadline+560 elapsed EXACT1 and signed rand()<8191, invoke40AC80(block,retained target,random FLOAT3..6). If current secondary!=11, saved policy nonzero and
// secondary!=1 and+560 elapsed EXACT1: secondary3 plus primary-flag20 EXACT1 resets route, compares current movement descriptor POINTER with445740(1) (registry fallback applies),
// calls40FD80 with same seven slots/that comparison flag, clears AI mask8, writes secondary0, computes401000 point and builds route to THAT point. Builder AL0 ->40AC80(...60.0f) and
// exit; any nonzero ->secondary1. Other admitted states compute401000 point BUT IGNORE it, build route to captured old COMMON target+60; EXACT AL1 ->secondary1 and set mask8
// iff437F60(owner)==EXACT1 OR visibility bytes any nonzero, else clear8. Other builder AL resets route and arms+560 inclusive500..1000ms. When saved policy AL0 and secondary1: if
// primary-flag20 predicate AL0 arm+564 with rand()%2000 plus base2000 if block DWORD+1308==1 else1000; reset route regardless; choose secondary3 if a fresh primary-flag20 result
// EXACT1 else2.407CF0(block) AL0 ->40AC80(...3.0f) and exit, otherwise write chosen state. In single-player ONLY and primary-flag20 predicate AL0: humanoid nonzero plus block
// DWORD+1184==2,secondary11,any visibility rearm+1272 inclusive1000..2000 AND+564 inclusive3000..4000 EACH reached call. If+1272 elapsed EXACT1 call449550; result EXACT0 OR1 (NOT
// unsigned<=1) rearms600..1200ms. Regardless of that result, secondary!=11,global entity681E38 nonnull,retained handle equals global handle and any visibility ->normalize(owner
// COMMON position-global retained point+2004), dot(global vector+2040); ordered strictly>DOUBLE0.949999988079071 arms+564 at0ms. Then+564 elapsed EXACT1 invokes4083A0 if
// secondary11,408090 if secondary2. Finally4085A0(block,captured COMMON target+60), native extra second arg ignored by that callee. If current mode7 exit;
// otherwise402F40(block),402EB0(block),402FD0(block,0), then live secondary1 runs401670 and407D90 only when class flags+1828 mask0x08000000; secondary2/3/11 always run both in that
// order; other states exit. No independent authority/owner-inactive admission or uniform result; stored int return is incidental.
void __cdecl rf_ai_numeric_mode3_update(float *Character)
{
  float v1; // [esp+14h] [ebp-58h]
  float out_vector[3]; // [esp+1Ch] [ebp-50h] BYREF
  unsigned int v3; // [esp+28h] [ebp-44h]
  int v4; // [esp+2Ch] [ebp-40h]
  int v5; // [esp+30h] [ebp-3Ch]
  int v6; // [esp+34h] [ebp-38h]
  float v7[3]; // [esp+38h] [ebp-34h] BYREF
  float v8[3]; // [esp+44h] [ebp-28h] BYREF
  char v9; // [esp+53h] [ebp-19h]
  int v10; // [esp+54h] [ebp-18h]
  char v11; // [esp+5Bh] [ebp-11h]
  float v12; // [esp+5Ch] [ebp-10h]
  bool v13; // [esp+62h] [ebp-Ah]
  char v14; // [esp+63h] [ebp-9h]
  int v15; // [esp+64h] [ebp-8h]
  float *v16; // [esp+68h] [ebp-4h]

  if ( rf_entity_is_dead(*(_DWORD *)Character) || rf_ai_scripted_action_has_remaining_time((int)Character) )
    return;
  if ( rf_entity_class_flags724_has_mask800(*(_DWORD *)Character) )
  {
    rf_ai_update_retained_target_route_policy((int)Character);
    return;
  }
  if ( rf_ai_should_seek_replacement_target((int *)Character) )
  {
    if ( rf_ai_primary_flag20_without_secondary((int)Character) )
    {
      v11 = 0;
      if ( !rf_entity_descriptor_mode_is_12_15_13_11_or9(*(_DWORD *)Character)
        || !rf_entity_movement_is_index4_or7(*(_DWORD *)Character) )
      {
        v11 = 1;
      }
      sub_40FD80(
        *(_DWORD *)Character + 60,
        Character[328],
        Character[329],
        v11,
        (int *)Character + 255,
        (int *)Character + 256,
        0);
      rf_ai_secondary_state_write((int)Character, 0);
    }
    rf_ai_scan_and_commit_weighted_target((int *)Character);
  }
  v15 = rf_object_resolve_handle(*((_DWORD *)Character + 176));
  if ( !v15 )
  {
    if ( rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(*(_DWORD *)Character + 44), *((_DWORD *)Character + 1)) )
      rf_entity_stop_weapon_firing(*(_DWORD *)(*(_DWORD *)Character + 44), *((_DWORD *)Character + 1));
    if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
      rf_ai_maybe_seek_any_waypoint_list((int)Character, 1);
    else
      sub_40A2A0((int *)Character);
    return;
  }
  v16 = (float *)rf_entity_resolve_handle(*((_DWORD *)Character + 176));
  if ( rf_entity_has_attached_use_vehicle((int)v16) )
  {
    v10 = rf_entity_resolve_handle(*((_DWORD *)v16 + 128));
    if ( v10 )
    {
      if ( !rf_entity_has_turret_flag(v10) )
        Character[176] = v16[128];
    }
  }
  if ( (rf_object_is_use_vehicle(v16) || rf_entity_has_turret_flag((int)v16))
    && !rf_entity_runtime_enabled_or_resolved_attachment((int)v16, -1)
    && *((_DWORD *)v16 + 328) == 1 )
  {
LABEL_27:
    sub_40BA80((int *)Character, -1);
    return;
  }
  v14 = 0;
  if ( *((_BYTE *)Character + 669) == 1 || *((_BYTE *)Character + 668) == 1 )
    v14 = 1;
  rf_ai_refresh_target_collision_and_corridor_probes((int *)Character, v15);
  if ( rf_ai_primary_flag20_without_secondary((int)Character)
    && (rf_entity_has_turret_flag((int)v16)
     || rf_entity_has_attached_use_turret((int)v16)
     || rf_object_is_use_vehicle(v16)) )
  {
    if ( *((_BYTE *)Character + 669) == 1 || *((_BYTE *)Character + 668) == 1 )
      sub_40AC80((int *)Character, *((_DWORD *)v16 + 11), 5.0);
  }
  else
  {
    if ( !*((_BYTE *)Character + 669) && !*((_BYTE *)Character + 668) && v14 == 1 )
      rf_timestamp_arm_random_inclusive_milliseconds((int *)Character + 142, 2000, 5000);
    v12 = *(float *)&dword_6FC428 - Character[166];
    if ( *(float *)(*(_DWORD *)(*(_DWORD *)Character + 660) + 1816) < (double)v12
      && !rf_multiplayer_runtime_mode
      && !rf_splitscreen_runtime_active )
    {
      goto LABEL_27;
    }
    v13 = rf_ai_target_needs_route_approach(Character);
    if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
    {
      if ( ((unsigned int)&unk_2000000 & (_DWORD)Character[332]) != 0 )
      {
        if ( rf_ai_route_update((int)(Character + 186)) != -1 )
          return;
        *((_DWORD *)Character + 332) &= ~0x2000000u;
      }
      else if ( rf_ai_build_alternative_route_from_global_points((int *)Character, 0) )
      {
        return;
      }
      if ( v13
        && *((_DWORD *)Character + 160) != 7
        && (*((_DWORD *)Character + 173) != 1 || !*((_DWORD *)Character + 186))
        && rf_replicator_has_elapsed((int *)Character + 140)
        && rand() < 0x1FFF )
      {
        v1 = rf_random_float_range(3.0, 6.0);
        sub_40AC80((int *)Character, *((_DWORD *)Character + 176), v1);
      }
    }
    if ( *((_DWORD *)Character + 173) != 11 )
    {
      if ( v13 )
      {
        if ( *((_DWORD *)Character + 173) != 1 && rf_replicator_has_elapsed((int *)Character + 140) )
        {
          if ( *((_DWORD *)Character + 173) == 3 && rf_ai_primary_flag20_without_secondary((int)Character) )
          {
            rf_ai_route_reset((int)(Character + 186));
            v9 = sub_445740(1u) == *(char **)(*(_DWORD *)Character + 2136);
            sub_40FD80(
              *(_DWORD *)Character + 60,
              Character[328],
              Character[329],
              v9,
              (int *)Character + 255,
              (int *)Character + 256,
              0);
            *((_DWORD *)Character + 332) &= ~8u;
            rf_ai_secondary_state_write((int)Character, 0);
            rf_vector3_default_construct_noop(v8);
            rf_ai_copy_route_target_position((int)Character, v8);
            if ( !rf_ai_route_build(*(_DWORD *)(*(_DWORD *)Character + 44), (int)v8) )
            {
              sub_40AC80((int *)Character, *((_DWORD *)Character + 176), 60.0);
              return;
            }
            rf_ai_secondary_state_write((int)Character, 1);
          }
          else
          {
            rf_vector3_default_construct_noop(v7);
            rf_ai_copy_route_target_position((int)Character, v7);
            if ( rf_ai_route_build(*(_DWORD *)(*(_DWORD *)Character + 44), v15 + 60) == 1 )
            {
              rf_ai_secondary_state_write((int)Character, 1);
              if ( rf_entity_descriptor_mode_is_12_15_13_11_or9(*(_DWORD *)Character)
                || *((_BYTE *)Character + 668)
                || *((_BYTE *)Character + 669) )
              {
                *((_DWORD *)Character + 332) |= 8u;
              }
              else
              {
                *((_DWORD *)Character + 332) &= ~8u;
              }
            }
            else
            {
              rf_ai_route_reset((int)(Character + 186));
              rf_timestamp_arm_random_inclusive_milliseconds((int *)Character + 140, 500, 1000);
            }
          }
        }
      }
      else if ( *((_DWORD *)Character + 173) == 1 )
      {
        if ( !rf_ai_primary_flag20_without_secondary((int)Character) )
        {
          v5 = rand() % 2000;
          v4 = 1000;
          if ( *((_DWORD *)Character + 327) == 1 )
            v4 = 2000;
          rf_replicator_arm_milliseconds((int *)Character + 141, v5 + v4);
        }
        rf_ai_route_reset((int)(Character + 186));
        v6 = 2;
        if ( rf_ai_primary_flag20_without_secondary((int)Character) )
          v6 = 3;
        if ( !rf_ai_primary_range_target_gate((int)Character) )
        {
          sub_40AC80((int *)Character, *((_DWORD *)Character + 176), 3.0);
          return;
        }
        rf_ai_secondary_state_write((int)Character, v6);
      }
    }
    if ( !rf_multiplayer_runtime_mode
      && !rf_splitscreen_runtime_active
      && !rf_ai_primary_flag20_without_secondary((int)Character) )
    {
      if ( rf_entity_has_humanoid_flag(*(_DWORD *)Character)
        && *((_DWORD *)Character + 296) == 2
        && *((_DWORD *)Character + 173) == 11
        && (*((_BYTE *)Character + 668) || *((_BYTE *)Character + 669)) )
      {
        rf_timestamp_arm_random_inclusive_milliseconds((int *)Character + 318, 1000, 2000);
        rf_timestamp_arm_random_inclusive_milliseconds((int *)Character + 141, 3000, 4000);
      }
      if ( rf_replicator_has_elapsed((int *)Character + 318) )
      {
        v3 = rf_ai_difficulty_get_with_zero_fallback();
        if ( v3 <= 1 )
          rf_timestamp_arm_random_inclusive_milliseconds((int *)Character + 318, 600, 1200);
        if ( *((_DWORD *)Character + 173) != 11
          && dword_681E38
          && *((_DWORD *)Character + 176) == *(_DWORD *)(dword_681E38 + 44)
          && (*((_BYTE *)Character + 668) || *((_BYTE *)Character + 669)) )
        {
          rf_vector_subtract(
            (const float *)(*(_DWORD *)Character + 60),
            out_vector,
            (const float *)(dword_681E38 + 2004));
          rf_vector_normalize(out_vector);
          if ( rf_vector_dot(out_vector, (float *)(dword_681E38 + 2040)) > 0.949999988079071 )
            rf_replicator_arm_milliseconds((int *)Character + 141, 0);
        }
      }
      if ( rf_replicator_has_elapsed((int *)Character + 141) )
      {
        if ( *((_DWORD *)Character + 173) == 11 )
        {
          rf_ai_select_secondary2_with_timing(Character);
        }
        else if ( *((_DWORD *)Character + 173) == 2 )
        {
          rf_ai_select_secondary11_after_reload_or_route_retry(Character);
        }
      }
    }
    rf_ai_face_target_and_advance_route(Character);
    if ( *((_DWORD *)Character + 160) != 7 )
    {
      rf_ai_maybe_seek_ammo_waypoints((int)Character);
      rf_ai_maybe_seek_weapon_waypoints((int *)Character);
      rf_ai_maybe_seek_any_waypoint_list((int)Character, 0);
      switch ( *((_DWORD *)Character + 173) )
      {
        case 1:
          if ( (*(_DWORD *)(*(_DWORD *)(*(_DWORD *)Character + 660) + 1828) & 0x8000000) != 0 )
          {
            rf_ai_dispatch_selected_primary_weapon_action((int *)Character);
            rf_ai_secondary_weapon_action_dispatch(Character);
          }
          break;
        case 2:
        case 3:
        case 0xB:
          rf_ai_dispatch_selected_primary_weapon_action((int *)Character);
          rf_ai_secondary_weapon_action_dispatch(Character);
          break;
        default:
          return;
      }
    }
  }
}

