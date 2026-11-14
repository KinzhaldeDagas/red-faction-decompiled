// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437850 rf_entity_mode3_or12_action_admitted
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required entity), explicit canonical AL0/1; no ownNULL guard or incomingST0. First entity DWORD+2420
// must differ from EXACT-1; every other negative passes this test. Primary weapon676 equal runtime grenade911CA8 OR riot-stick911C94 rejects. Movement predicate437F60 EXACTAL1
// rejects; every other byte proceeds. Priority branch modeDWORD1312==3 AND entityDWORD1856==2 returns whether secondaryDWORD1364==11 immediately, bypassing all later
// geometry/fallback checks.  Otherwise mode3 AND entityDWORD1980==1: secondary1 or11 rejects; all other secondary values COMMON-resolve full target handle1376. Missing/stale target
// returnsAL1. Resolved COMMON target is copied through4BCCB0 into target point (ENTITY retained+2004 if applicable, otherwise COMMON+60), return ignored. Rotate class vector+168 by
// entity COMMON matrix72 via559150, store float32 components; add entity COMMON position60 with float32 component stores to get query start.
// Calls4D0220(start,targetPoint,DWORD0x27,0), rejects ONLY EXACTAL1; every other byte—including other nonzero—returnsAL1. This geometry helper tests serialized solids/world, not all
// runtime-object collision lists.  Every other mode/state combination enters final predicate: mode1312==12 AND secondary1364!=1 AND entityDWORD1260==1 AND entityDWORD2000 mask0x4000
// set yieldsAL1, elseAL0. No target resolution/line query for final mode12 branch; no secondary11 exclusion there. No own ammo/ownership/range/player/dead/authority test, acquisition
// or storage writes. Calls and priority short circuits retain native order.
bool __cdecl rf_entity_mode3_or12_action_admitted(int a1)
{
  bool result; // al
  float *v2; // eax
  float v3[3]; // [esp+0h] [ebp-28h] BYREF
  float sum_result[3]; // [esp+Ch] [ebp-1Ch] BYREF
  float v5[3]; // [esp+18h] [ebp-10h] BYREF
  int v6; // [esp+24h] [ebp-4h]

  if ( *(_DWORD *)(a1 + 2420) == -1 )
    return 0;
  if ( *(_DWORD *)(a1 + 676) == rf_weapon_index_grenade || *(_DWORD *)(a1 + 676) == rf_weapon_id_riot_stick )
    return 0;
  if ( rf_entity_descriptor_mode_is_12_15_13_11_or9(a1) )
    return 0;
  if ( *(_DWORD *)(a1 + 1312) == 3 && *(_DWORD *)(a1 + 1856) == 2 )
    return *(_DWORD *)(a1 + 1364) == 11;
  if ( *(_DWORD *)(a1 + 1312) != 3 || *(_DWORD *)(a1 + 1980) != 1 )
    return *(_DWORD *)(a1 + 1312) == 12
        && *(_DWORD *)(a1 + 1364) != 1
        && *(_DWORD *)(a1 + 1260) == 1
        && (*(_DWORD *)(a1 + 2000) & 0x4000) != 0;
  if ( *(_DWORD *)(a1 + 1364) == 1 || *(_DWORD *)(a1 + 1364) == 11 )
  {
    return 0;
  }
  else
  {
    rf_vector3_default_construct_noop(v5);
    v6 = rf_object_resolve_handle(*(_DWORD *)(a1 + 1376));
    result = true;
    if ( v6 )
    {
      rf_object_copy_entity_vector7D4_or_position(v6, v5);
      v2 = rf_matrix3_rotate_vector((float *)(*(_DWORD *)(a1 + 660) + 168), v3, (float *)(a1 + 72));
      rf_vector_add((const float *)(a1 + 60), sum_result, v2);
      if ( rf_geometry_segment_is_obstructed((int)sum_result, (int)v5, 39, 0) == 1 )
        return false;
    }
  }
  return result;
}

