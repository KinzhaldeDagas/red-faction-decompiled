// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00440440 rf_entity_emit_movement_foley_from_shared_distance
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(entity), void; attached-use-vehicle436A80 EXACT AL1 or dead433F60 EXACT AL1 exits. Uses SHARED globals:
// thresholds T=6E6714,C=6E6718,pan P=6E671C,ordinary distance O=6E6720,descriptor2 distance D=6E6724; no per-entity timer/previous-position storage here.43CAA0 descriptor2 predicate
// ANY nonzero takes first branch: only ORDERED C<D triggers one step; equality/NaN skip trigger. Read raw index=DWORD[entity5104], no control/index guard; class660 group416+4*index
// SIGNED>=0 admits sound/stimulus, negative skips them but STILL flips pan and resets D0. Ordered P<0 selects first sound-list half; P>=0 OR UNORDERED selects second. Count446FB0 is
// divided by2 using CDQ/SUB/SAR, truncating towardZERO; second half uses base447080+4*half and RE-READS count for playback half. No positive count/list guard: invalid group getters
// return count-1/base0, and4BCD20 count<=1 STILL reads list[0], not safe no-op. Calls4BCD20 with EIGHT DWORD slots(entity,BY-VALUE positionXYZ,list,half,FLOAT1,FLOATpan), ignoring
// asset/play result, then40A810(uid,position,FLOAT3,policyBYTE0,EXTRA ignoredDWORD0), regardless sound success. After any triggered step, P=FCHS(P),D=0. Always
// D=round32(length(entity324)*frameDeltaSeconds+D) with no product store before add, then O=0 and exit. If descriptor2 false, require437EC0 ANY nonzero OR437E80 ANY nonzero OR
// crouch40CED0 ANY nonzero, in that short-circuit order; otherwise no accumulator writes. Step triggers only ORDERED O>T*DOUBLE1.5 when multiplayer BYTE nonzero, or ORDERED T<O when
// zero; mode byte reread. Equality/NaN skips trigger but still accumulates at end. Trigger first stores entity material4992=0 if signed-negative, with no upper bound. Runtime2064
// mask1000 plus movement1/2 ANYnonzero requires class group392 SIGNED>=0 and chooses index4; missing group RETURNS WHOLE FUNCTION before pan/accumulator updates. Otherwise raw class
// group376+4*material>=0 selects material, else valid group376 selects LOCAL index0 without repairing positive entity material; missing fallback also returns before final
// accumulation. Then crouch EXACT AL1 overrides chosen group with class428, WITHOUT validating replacement group or bypassing earlier group admission. Main/glass halfcount uses
// arithmetic SAR1, flooring negative counts, unlike descriptor2 truncation. P<0 selects first list half, P>=0 OR NaN second; same eight-slot sound/stimulus call as above.
// Glass-overlap4C7670 ANYnonzero additionally plays group global661570 with same SAR half/sign selection, but NO second stimulus and no group-validity guard. After plays flip P, then
// O=round32((fresh multiplayer?T*DOUBLE1.5:T)-OLD O), NOT O-threshold. Finally O=round32(length324*frameDeltaSeconds+O) and D=0. At most one main step plus optional glass sound per
// call; no loop to consume overshoot. Signedzero pan compares nonnegative even after FCHS, NaN selects second half and remains NaN; no finite/clamp/reentrancy/authority guard or
// rollback of material/sound/RNG/stimulus prefixes.
void __cdecl rf_entity_emit_movement_foley_from_shared_distance(int a1)
{
  int v1; // eax
  double v2; // st7
  float v3; // [esp-10h] [ebp-50h] BYREF
  int v4; // [esp-Ch] [ebp-4Ch]
  int v5; // [esp-8h] [ebp-48h]
  int v6; // [esp-4h] [ebp-44h]
  int v7; // [esp+0h] [ebp-40h]
  float v8; // [esp+4h] [ebp-3Ch]
  float v9; // [esp+8h] [ebp-38h]
  int v10; // [esp+24h] [ebp-1Ch]
  int v11; // [esp+28h] [ebp-18h]
  int v12; // [esp+2Ch] [ebp-14h]
  int v13; // [esp+30h] [ebp-10h]
  int v14; // [esp+34h] [ebp-Ch]
  int v15; // [esp+38h] [ebp-8h]
  int v16; // [esp+3Ch] [ebp-4h]

  if ( !rf_entity_has_attached_use_vehicle(a1) && !rf_entity_is_dead(a1) )
  {
    if ( rf_entity_movement_descriptor_kind_is2(a1) )
    {
      if ( unk_6E6718 < (double)unk_6E6724 )
      {
        v16 = **(_DWORD **)(a1 + 5104);
        if ( *(int *)(*(_DWORD *)(a1 + 660) + 4 * v16 + 416) >= 0 )
        {
          if ( unk_6E671C >= 0.0 )
          {
            v15 = rf_foley_group_sound_array(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * v16 + 416));
            v15 += 4 * (rf_foley_group_sound_count(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * v16 + 416)) / 2);
            v9 = unk_6E671C;
            v8 = 1.0;
            v7 = rf_foley_group_sound_count(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * v16 + 416)) / 2;
            v6 = v15;
          }
          else
          {
            v9 = unk_6E671C;
            v8 = 1.0;
            v7 = rf_foley_group_sound_count(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * v16 + 416)) / 2;
            v6 = rf_foley_group_sound_array(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * v16 + 416));
          }
          rf_vector3_copy_return_destination(&v3, (float *)(a1 + 60));
          rf_sound_list_select_play_return_asset(a1, v3, v4, v5, v6, v7, v8, v9);
          v9 = 0.0;
          rf_ai_propagate_stimulus_to_nearby_entities(*(_DWORD *)(a1 + 44), (float *)(a1 + 60), 3.0, 0);
        }
        unk_6E671C = -unk_6E671C;
        unk_6E6724 = 0.0;
      }
      unk_6E6724 = rf_vector3_length((float *)(a1 + 324)) * rf_frame_delta_seconds + unk_6E6724;
      unk_6E6720 = 0.0;
    }
    else if ( rf_entity_descriptor_mode1_and_speedmode1(a1) || sub_437E80(a1) || rf_entity_is_crouched_state810(a1) )
    {
      if ( rf_multiplayer_runtime_mode && unk_6E6720 > unk_6E6714 * 1.5
        || !rf_multiplayer_runtime_mode && unk_6E6714 < (double)unk_6E6720 )
      {
        if ( *(int *)(a1 + 4992) < 0 )
          *(_DWORD *)(a1 + 4992) = 0;
        v12 = -1;
        if ( (*(_DWORD *)(a1 + 2064) & 0x1000) != 0 && rf_entity_movement_is_index1_or2(a1) )
        {
          if ( *(int *)(*(_DWORD *)(a1 + 660) + 392) < 0 )
            return;
          v12 = 4;
        }
        else if ( *(int *)(*(_DWORD *)(a1 + 660) + 4 * *(_DWORD *)(a1 + 4992) + 376) < 0 )
        {
          if ( *(int *)(*(_DWORD *)(a1 + 660) + 376) < 0 )
            return;
          v12 = 0;
        }
        else
        {
          v12 = *(_DWORD *)(a1 + 4992);
        }
        v13 = *(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * v12 + 376);
        if ( rf_entity_is_crouched_state810(a1) )
          v13 = *(_DWORD *)(*(_DWORD *)(a1 + 660) + 428);
        v14 = rf_foley_group_sound_count(v13) >> 1;
        if ( unk_6E671C >= 0.0 )
        {
          v11 = rf_foley_group_sound_array(v13) + 4 * v14;
          v9 = unk_6E671C;
          v8 = 1.0;
          v7 = v14;
          v6 = v11;
        }
        else
        {
          v9 = unk_6E671C;
          v8 = 1.0;
          v7 = v14;
          v6 = rf_foley_group_sound_array(v13);
        }
        rf_vector3_copy_return_destination(&v3, (float *)(a1 + 60));
        rf_sound_list_select_play_return_asset(a1, v3, v4, v5, v6, v7, v8, v9);
        v9 = 0.0;
        rf_ai_propagate_stimulus_to_nearby_entities(*(_DWORD *)(a1 + 44), (float *)(a1 + 60), 3.0, 0);
        if ( rf_glass_resting_shard_overlap_test((float *)a1) )
        {
          v13 = dword_661570;
          v14 = rf_foley_group_sound_count(dword_661570) >> 1;
          if ( unk_6E671C >= 0.0 )
          {
            v1 = rf_foley_group_sound_array(v13);
            v10 = v1 + 4 * v14;
            v9 = unk_6E671C;
            v8 = 1.0;
            v7 = v14;
            v6 = v10;
          }
          else
          {
            v9 = unk_6E671C;
            v8 = 1.0;
            v7 = v14;
            v6 = rf_foley_group_sound_array(v13);
          }
          rf_vector3_copy_return_destination(&v3, (float *)(a1 + 60));
          rf_sound_list_select_play_return_asset(a1, v3, v4, v5, v6, v7, v8, v9);
        }
        unk_6E671C = -unk_6E671C;
        if ( rf_multiplayer_runtime_mode )
          v2 = unk_6E6714 * 1.5 - unk_6E6720;
        else
          v2 = unk_6E6714 - unk_6E6720;
        unk_6E6720 = v2;
      }
      unk_6E6720 = rf_vector3_length((float *)(a1 + 324)) * rf_frame_delta_seconds + unk_6E6720;
      unk_6E6724 = 0.0;
    }
  }
}

