// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00401B60 rf_ai_primary_weapon_ready_with_stop_request
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Cdecl(required output BYTE pointer,required AI block). Initializes output=0 IMMEDIATELY; returns explicit
// AL0/1 separately. COMMON target full handle+704 missing ->output1/return0. Deadline+536 elapsed AL0 ->return0/output0. Require visibility BYTE+668 or+669 any nonzero OR AI
// flags+1328 mask0x1000; otherwise output1/return0. Target common health+52 ordered<=0 ->output1/return0; POSITIVE OR UNORDERED continues (native AH41/JP). Owner fall/airborne
// movement predicate437F00==EXACT AL1 sets output1, ORs AI mask0x8000, arms block+1204 inclusive100..400 milliseconds, returns0. No direct target-player/authority gate. Otherwise
// invoke4014F0(block,0), ignore return, then re-read SIGNED primary index+4: only index>-1 forms rf_weapon_records+1360*index; no upper bound. No record pointer ->return0/output0.
// Single-player (both runtime/splitscreen BYTE0), class flags+1828 mask0x08000000 clear and secondary state+692==1 ->output1/return0; other states/runtime/class flag continue.
// Euclidean COMMON-position distance roundsfloat32. Selected weapon record FLOAT+204 ordered<distance ->output1/return0; range>=distance OR UNORDERED passes. AI mask0x8000 already
// set ->output1/return0. Class mask0x08000000 bypasses next attack-range check; otherwise call primary range resolver(block,1). Ordered distance>range AND block DWORD+1184==2
// ->output1/return0; distance<=range OR unordered, or DWORD+1184!=2, continues. Copy owner retained point+2004 to rhs; no-write lhs constructor,4010E0(block,COMMON target,&lhs),
// ignore helper return; normalize(lhs-rhs) unchecked, dot owner vector+2040, roundfloat32. Ordered dot<DOUBLE0.9 ->output1/return0; dot>=0.9 OR UNORDERED admits. AI mask0x100000:
// resolve owner attachment+512 as ENTITY; ONLY if parent resolves AND parent ready predicate AL0 return0/output0. Missing parent DOES NOT block, and parent ready any nonzero passes.
// AI mask0x20000000 then unconditionally returns0/output0. Admitted owner humanoid predicate nonzero plus primary mode3 and global6663E4 deadline DISARMED optionally arm that shared
// deadline:401EF0 nonzero ->rand()%4000+6000ms, else rand()%3000+7000ms. ReturnsAL1 with output STILL0 regardless of optional timer path. Thus output1 rejections are missing target,
// visibility/health/fall state, SP-secondary1 restriction, weapon maximum-range failure, existing0x8000, primary-range/1184 gate or aim-dot failure; output0 rejections are
// nonelapsed+536, invalid negative primary, resolved-unready parent or mask0x20000000. No direct ammo decrement, projectile creation, geometry ray, pending-friendly-byte670 test, or
// stop-deadline+556 handling here; outer401670 owns later action/stop policy.
char __cdecl rf_ai_primary_weapon_ready_with_stop_request(_BYTE *a1, int *a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // [esp+0h] [ebp-38h]
  float lhs[3]; // [esp+4h] [ebp-34h] BYREF
  float rhs[3]; // [esp+10h] [ebp-28h] BYREF
  float v8; // [esp+1Ch] [ebp-1Ch]
  float out_vector[3]; // [esp+20h] [ebp-18h] BYREF
  float *v10; // [esp+2Ch] [ebp-Ch]
  int v11; // [esp+30h] [ebp-8h]
  float v12; // [esp+34h] [ebp-4h]

  *a1 = 0;
  v11 = rf_object_resolve_handle(a2[176]);
  if ( v11 )
  {
    if ( rf_replicator_has_elapsed(a2 + 134) )
    {
      if ( *((_BYTE *)a2 + 668) || *((_BYTE *)a2 + 669) || (a2[332] & 0x1000) != 0 )
      {
        if ( *(float *)(v11 + 52) > 0.0 )
        {
          if ( rf_entity_uses_fall_or_airborne_vehicle_motion(*a2) )
          {
            *a1 = 1;
            a2[332] |= 0x8000u;
            rf_timestamp_arm_random_inclusive_milliseconds(a2 + 301, 100, 400);
            return 0;
          }
          else
          {
            v10 = nullptr;
            sub_4014F0(a2, 0);
            if ( a2[1] > -1 )
              v10 = (float *)((char *)&rf_weapon_records + 1360 * a2[1]);
            if ( v10 )
            {
              if ( rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode
                || (*(_DWORD *)(*(_DWORD *)(*a2 + 660) + 1828) & 0x8000000) != 0
                || a2[173] != 1 )
              {
                v12 = rf_vector_distance((const float *)(*a2 + 60), (const float *)(v11 + 60));
                if ( v10[51] >= (double)v12 )
                {
                  if ( (a2[332] & 0x8000) != 0 )
                  {
                    *a1 = 1;
                    return 0;
                  }
                  else if ( (*(_DWORD *)(*(_DWORD *)(*a2 + 660) + 1828) & 0x8000000) != 0
                         || v12 <= rf_ai_resolve_attack_range((int)a2, 1)
                         || a2[296] != 2 )
                  {
                    rf_vector3_copy_return_destination(rhs, (float *)(*a2 + 2004));
                    rf_vector3_default_construct_noop(lhs);
                    rf_ai_copy_target_point_for_current_movement(a2, v11, lhs);
                    rf_vector_subtract(lhs, out_vector, rhs);
                    rf_vector_normalize_reciprocal_sqrt(out_vector);
                    v8 = rf_vector_dot((float *)(*a2 + 2040), out_vector);
                    if ( v8 >= 0.9 )
                    {
                      if ( (a2[332] & 0x100000) != 0
                        && (v5 = rf_entity_resolve_handle(*(_DWORD *)(*a2 + 512))) != 0
                        && !rf_ai_is_ready_flag_set(v5 + 672) )
                      {
                        return 0;
                      }
                      else if ( (a2[332] & 0x20000000) != 0 )
                      {
                        return 0;
                      }
                      else
                      {
                        if ( rf_entity_has_humanoid_flag(*a2) && a2[160] == 3 && !rf_replicator_is_armed(&dword_6663E4) )
                        {
                          if ( rf_ai_has_unholstered_mode3_peer_on_same_target(a2) )
                          {
                            v3 = rand();
                            rf_replicator_arm_milliseconds(&dword_6663E4, v3 % 4000 + 6000);
                          }
                          else
                          {
                            v4 = rand();
                            rf_replicator_arm_milliseconds(&dword_6663E4, v4 % 3000 + 7000);
                          }
                        }
                        return 1;
                      }
                    }
                    else
                    {
                      *a1 = 1;
                      return 0;
                    }
                  }
                  else
                  {
                    *a1 = 1;
                    return 0;
                  }
                }
                else
                {
                  *a1 = 1;
                  return 0;
                }
              }
              else
              {
                *a1 = 1;
                return 0;
              }
            }
            else
            {
              return 0;
            }
          }
        }
        else
        {
          *a1 = 1;
          return 0;
        }
      }
      else
      {
        *a1 = 1;
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    *a1 = 1;
    return 0;
  }
}

