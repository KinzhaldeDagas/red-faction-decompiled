// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436AD0 rf_entity_update_liquid_flags_motion_and_shared_sound
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required entity), void/incidental register result. Reads/captures current room POINTER from
// DWORD[entity+0] using486DE0; no own entityNULL guard. NULL room clears COMMON flags DWORD+124 mask0x80000 and entity flags DWORD+2064 mask0x3000, then RETURNS without changing
// physics428 mask1000, movement, shared voice66131C or flags2068 mask800. Nonnull room first copies CURRENT PHYSICS position+228 and calls517AF0(room,&copy); ANY nonzero AL means
// submerged for this branch. Verified liquid helper only tests enable BYTE388 any-nonzero and ordered pointY<=unrounded room.minY12+depth392; no X/Z containment, NaN fails.  Initial
// submerged branch ORs common124 mask80000, then entity2064 mask1000. If angular-decay class predicate43C950 ANY nonzero (class1828 intersects0x401200), special branch owns
// remainder: if global local entity681E38 nonnull AND its parent DWORD512 equals input entity fullhandle44, ENTITY-resolves that parent and captures result, then calls434C80(global
// entity), requiring ANY nonzero AL for suffix. Successful outer detach does not prove reciprocal detach/snap-down success. Re-reads global681E38 to copy its current class
// vectors+108/+120 into entity vectors+5172/+5184, respectively. If captured pre-detach parent passes use-vehicle437690 ANY nonzero, writes local entity
// FLOAT2172=FLOAT32(parent2148+parent2172), then FLOAT2152=FLOAT32(parent2152+parent2176); zeroes PARENT vectors324,348,336 in that order. If re-read local entity
// primary676==global911C80 calls guarded holster-clear436750(local), ignoring result. Captured parent is not re-resolved; use-vehicle safely rejectsNULL. Regardless of local entity
// absence/parent mismatch/detach failure, ORs INPUT entity flags2068 mask800 and RETURNS. This branch preserves prior entity2064 mask2000, physics428 mask1000 and shared voice; skips
// retained-point liquid/weapon-stop path.  Non-angular branch: fall/airborne-motion437F00 ANY nonzero calls435810(entity), ignores result. Then liquid-tests same captured room
// against retained entity point+2004. ANY nonzero ORs entity2064 mask2000; if movement-is4or7 predicate437FD0 AL0 calls435810 again (can have two calls, no own success gate). If
// shared voice66131C!=-1 AND player flag4BB430 ANY nonzero, stops that voice and stores global-1. Always stops INPUT PRIMARY weapon firing422A40(entity fullhandle44,primary676),
// regardless of shared voice/player/movement results. Retained-point liquid AL0 instead clears entity2064 mask2000; player flag AL0 exits. Any-nonzero player flag: if shared
// voice==-1 plays nonpositional event17(0,FLOAT0,FLOAT1) and saves FULL EAX including-1; existing any-not-1 value is reused without is-playing check. Ratio=FLOAT32(vector
// length40CFA0(entity+324) ST0 / class FLOAT+80), then gain=FLOAT32(ratio*DOUBLE0.4000000059604645+DOUBLE0.6000000238418579), no intermediate product store. Clamp in
// place40D620(gain,0,1) leaves NaN unchanged; no class-speed zero/finite guard. Calls5685A0(shared voice,gain,FLOAT0 pan), even if play failed and handle=-1.  Initial PHYSICS-point
// liquid AL0 branch instead clears common80000, entity3000, then ORs physics DWORD+428 mask1000. Movement4or7 ANY nonzero calls fall-selector4356E0, ignores result. Shared voice!=-1
// plus player flag ANY nonzero stops and resets voice. Then movement1or2 predicate438050 ANY nonzero constructs bottom point from COMMON position X/Z and Y=FLOAT32(entity COMMONY64 -
// radiusFLOAT384*DOUBLE0.800000011920929), without intermediate product rounding. Liquid-test of this point ANY nonzero ORs entity2064 mask1000 and clears physics428 mask1000;
// common80000 and entity2000 stay cleared. Does not reacquire room after delegates. No own dead/authority/humanoid gate, pose rollback or symmetric cleanup across the distinct
// NULL-room/special-class/ordinary liquid paths; shared sound is GLOBAL, not per entity.
void __cdecl rf_entity_update_liquid_flags_motion_and_shared_sound(int a1)
{
  float v1; // [esp+Ch] [ebp-44h]
  float v2[3]; // [esp+10h] [ebp-40h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-34h] BYREF
  float v4[3]; // [esp+28h] [ebp-28h] BYREF
  float v5; // [esp+34h] [ebp-1Ch]
  int v6; // [esp+38h] [ebp-18h] BYREF
  float *v7; // [esp+3Ch] [ebp-14h]
  int first_dword; // [esp+40h] [ebp-10h]
  float v9[3]; // [esp+44h] [ebp-Ch] BYREF

  first_dword = rf_receiver_get_first_dword((void *)a1);
  if ( first_dword )
  {
    rf_vector3_copy_return_destination(v9, (float *)(a1 + 228));
    if ( rf_liquid_room_contains_point(first_dword, (int)v9) )
    {
      *(_DWORD *)(a1 + 124) |= 0x80000u;
      *(_DWORD *)(a1 + 2064) |= 0x1000u;
      if ( rf_entity_class_has_angular_decay_flags(a1) )
      {
        if ( dword_681E38 )
        {
          if ( *(_DWORD *)(dword_681E38 + 512) == *(_DWORD *)(a1 + 44) )
          {
            v7 = (float *)rf_entity_resolve_handle(*(_DWORD *)(dword_681E38 + 512));
            if ( rf_entity_try_detach_with_safe_exit(dword_681E38) )
            {
              rf_vector_copy(
                (float *)(dword_681E38 + 5172),
                copy_result,
                (const float *)(*(_DWORD *)(dword_681E38 + 660) + 108));
              rf_vector_copy((float *)(dword_681E38 + 5184), v2, (const float *)(*(_DWORD *)(dword_681E38 + 660) + 120));
              if ( rf_object_is_use_vehicle(v7) )
              {
                *(float *)(dword_681E38 + 2172) = v7[537] + v7[543];
                *(float *)(dword_681E38 + 2152) = v7[538] + v7[544];
                rf_vector3_zero_return_destination(v7 + 81);
                rf_vector3_zero_return_destination(v7 + 87);
                rf_vector3_zero_return_destination(v7 + 84);
                if ( *(_DWORD *)(dword_681E38 + 676) == unk_911C80 )
                  rf_entity_clear_holster_if_mapped_weapon_owned((_DWORD *)dword_681E38);
              }
            }
          }
        }
        *(_DWORD *)(a1 + 2068) |= 0x800u;
      }
      else
      {
        if ( rf_entity_uses_fall_or_airborne_vehicle_motion(a1) )
          rf_entity_select_movement4_or7(a1);
        if ( rf_liquid_room_contains_point(first_dword, a1 + 2004) )
        {
          *(_DWORD *)(a1 + 2064) |= 0x2000u;
          if ( !rf_entity_movement_is_index4_or7(a1) )
            rf_entity_select_movement4_or7(a1);
          if ( dword_66131C != -1 && rf_object_has_player_flag(a1) )
          {
            rf_gamesound_stop_voice_handle(dword_66131C);
            dword_66131C = -1;
          }
          rf_entity_stop_weapon_firing(*(_DWORD *)(a1 + 44), *(_DWORD *)(a1 + 676));
        }
        else
        {
          *(_DWORD *)(a1 + 2064) &= ~0x2000u;
          if ( rf_object_has_player_flag(a1) )
          {
            if ( dword_66131C == -1 )
              dword_66131C = rf_gamesound_play_event(17, 0, 0.0, 1.0);
            v5 = rf_vector3_length((float *)(a1 + 324)) / *(float *)(*(_DWORD *)(a1 + 660) + 80);
            *(float *)&v6 = v5 * 0.4000000059604645 + 0.6000000238418579;
            rf_float_clamp_in_place((float *)&v6, 0.0, 1.0);
            rf_gamesound_voice_set_gain_and_pan(dword_66131C, *(float *)&v6, 0.0);
          }
        }
      }
    }
    else
    {
      *(_DWORD *)(a1 + 124) &= ~0x80000u;
      *(_DWORD *)(a1 + 2064) &= 0xFFFFCFFF;
      *(_DWORD *)(a1 + 428) |= 0x1000u;
      if ( rf_entity_movement_is_index4_or7(a1) )
        rf_entity_select_fall_movement_descriptor((_DWORD *)a1);
      if ( dword_66131C != -1 && rf_object_has_player_flag(a1) )
      {
        rf_gamesound_stop_voice_handle(dword_66131C);
        dword_66131C = -1;
      }
      if ( rf_entity_movement_is_index1_or2(a1) )
      {
        v1 = *(float *)(a1 + 64) - *(float *)(a1 + 384) * 0.800000011920929;
        rf_vector3_set_components_return_destination(v4, *(float *)(a1 + 60), v1, *(float *)(a1 + 68));
        if ( rf_liquid_room_contains_point(first_dword, (int)v4) )
        {
          *(_DWORD *)(a1 + 2064) |= 0x1000u;
          *(_DWORD *)(a1 + 428) &= ~0x1000u;
        }
      }
    }
  }
  else
  {
    *(_DWORD *)(a1 + 124) &= ~0x80000u;
    *(_DWORD *)(a1 + 2064) &= 0xFFFFCFFF;
  }
}

