// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00406360 rf_ai_mode7_route_and_target_update
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, central mode7 handler. Damage/flinch override(owner)==EXACT AL1 exits all work. Resolve
// COMMON target+704; missing calls40A2A0 then exits. Class walk predicate435440 any-nonzero AND fall/airborne predicateAL0 calls movement-reset4355A0, ignoring result. Route-update
// native stack(route+744,extra0), clean8. ONLY EAX==-1 enters reaction branch:4025D0 probes; both bytes+668/+669 zero admit immediately, otherwise40DF30(owner handle,target
// COMMON+60)==AL0 admits. Any nonzero multiplayer/splitscreen then40B2D0 followed guarded target-set40BA80(target full handle), without return gate. Single-player requires humanoid
// EXACT1 and block+1236 deadline elapsed EXACT1; calls random FLOAT10000..15000 and directly truncates returnedST0 LOW32 into millisecond arm, without extra float32 duration store,
// BEFORE further speech conditions. Speech requires global entity681E38 nonnull, ordered squared COMMON-position distance<DOUBLE25, body-state-resident(owner,13) any nonzero, at
// least one probe byte nonzero, owner+2068 mask0x200 clear; chooses4412B0(class voice index+1780), replaces speech(owner,sound,0) even-1. Independently deadline+592 elapsed EXACT1:
// selected-weapon predicate40B6D0==EXACT1 ->40B2D0 then guarded target-set; all other AL ->40A2A0. Calls405030(block) afterwards even when that fallback changed mode. Route results
// other than-1 skip reaction branch but retain deadline/postlude work.
void __cdecl rf_ai_mode7_route_and_target_update(int *a1)
{
  double v1; // st7
  int v2; // [esp+8h] [ebp-10h]
  char v3; // [esp+Fh] [ebp-9h]
  int v4; // [esp+14h] [ebp-4h]

  if ( rf_character_update_damage_flinch_override(*a1) != 1 )
  {
    v4 = rf_object_resolve_handle(a1[176]);
    if ( v4 )
    {
      if ( rf_entity_class_flags724_has_mask1(*a1) && !rf_entity_uses_fall_or_airborne_vehicle_motion(*a1) )
        sub_4355A0(*a1);
      if ( rf_ai_route_update((int)(a1 + 186)) == -1 )
      {
        v3 = 0;
        rf_ai_refresh_target_collision_and_corridor_probes(a1, v4);
        if ( *((_BYTE *)a1 + 668) || *((_BYTE *)a1 + 669) )
        {
          if ( !rf_ai_build_avoid_route_with_target_adjustment(*(_DWORD *)(*a1 + 44), v4 + 60) )
            v3 = 1;
        }
        else
        {
          v3 = 1;
        }
        if ( v3 )
        {
          if ( rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode )
          {
            sub_40B2D0(a1);
            sub_40BA80(a1, *(_DWORD *)(v4 + 44));
          }
          else if ( rf_entity_has_humanoid_flag(*a1) && rf_replicator_has_elapsed(a1 + 309) )
          {
            v1 = rf_random_float_range(10000.0, 15000.0);
            rf_replicator_arm_milliseconds(a1 + 309, (int)v1);
            if ( dword_681E38 )
            {
              if ( rf_vector_distance_squared((const float *)(dword_681E38 + 60), (const float *)(*a1 + 60)) < 25.0
                && rf_entity_body_state_is_resident(*a1, 13)
                && (*((_BYTE *)a1 + 668) || *((_BYTE *)a1 + 669))
                && (*(_DWORD *)(*a1 + 2068) & 0x200) == 0 )
              {
                v2 = rf_registry56_choose_sound_at_6E6740(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
                rf_entity_replace_speech_voice(*a1, v2, 0);
              }
            }
          }
        }
      }
      if ( rf_replicator_has_elapsed(a1 + 148) )
      {
        if ( sub_40B6D0(a1) == 1 )
        {
          sub_40B2D0(a1);
          sub_40BA80(a1, *(_DWORD *)(v4 + 44));
        }
        else
        {
          sub_40A2A0(a1);
        }
      }
      sub_405030(a1);
    }
    else
    {
      sub_40A2A0(a1);
    }
  }
}

