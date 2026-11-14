// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00408090 rf_ai_select_secondary11_after_reload_or_route_retry
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block. Attached-use-turret EXACT AL1 immediately writes secondary2; no further work. Otherwise
// block DWORD+1184==2 AND humanoid EXACT1: positive-clip predicate(primary+4)==EXACT1 permits unchecked weapon record reads; loads912024+1360*primary to an UNUSED ammo-index local,
// but compares HALF SIGNED clip-size DWORD912080+1360*primary against SIGNED loaded count at AI+140+4*PRIMARY WEAPON INDEX (not loaded[ammoIndex]). Strict ordered halfclip>loaded
// requests reload(owner pointer,1,0). Then always stops primary firing, arms block+564 inclusive1000..3000ms, writes secondary11. Else class-mask0x800 predicate EXACT1 ->40EAB0(owner
// full handle), arm+564 inclusive3000..8000, OR flags+1328 mask8, secondary11. General branch: target ENTITY resolves, has nonnull player pointer+5168 and reversed
// angular4024E0(target,owner) AL0 ->only arm+564 inclusive200..500ms and exit, leaving route/secondary/fire untouched. Otherwise resolve COMMON target. Found: initialize attempts0
// and scorefloat0, no-write output vector; while score ordered<DOUBLE9 AND signed attempts<4,40EAB0(owner handle), then402BA0(target COMMON+60,AI+772,AI+896,&vector), round returned
// scorefloat32,increment attempts. Exactly4 attempts with score still ordered<9 resets embedded route+744 and exits WITHOUT final state/timer/fire effects. NaN stops attempts and
// follows final branch, not failure reset. Missing COMMON target also enters final branch. Final:422270(owner handle,primary index)==EXACT1 optionally stops firing; arm+564 with
// rand()%1000+300ms, OR mask8, write secondary11. No own player/death/inactive/multiplayer/authority gate or uniform return status.
int __cdecl rf_ai_select_secondary11_after_reload_or_route_retry(_DWORD *a1)
{
  float v2[3]; // [esp+0h] [ebp-24h] BYREF
  float v3; // [esp+Ch] [ebp-18h]
  int v4; // [esp+10h] [ebp-14h]
  int v5; // [esp+14h] [ebp-10h]
  int v6; // [esp+18h] [ebp-Ch]
  int v7; // [esp+1Ch] [ebp-8h]
  int v8; // [esp+20h] [ebp-4h]

  if ( rf_entity_has_attached_use_turret(*a1) )
    return rf_ai_secondary_state_write((int)a1, 2);
  if ( a1[296] == 2 && rf_entity_has_humanoid_flag(*a1) )
  {
    if ( rf_weapon_has_positive_clip_size(a1[1]) )
    {
      v5 = dword_912024[340 * a1[1]];
      if ( (double)unk_912080[340 * a1[1]] * 0.5 > (double)(int)a1[a1[1] + 35] )
        rf_weapon_reload_request(*a1, 1, 0);
    }
    rf_entity_stop_weapon_firing(*(_DWORD *)(*a1 + 44), a1[1]);
    rf_timestamp_arm_random_inclusive_milliseconds(a1 + 141, 1000, 3000);
    return rf_ai_secondary_state_write((int)a1, 11);
  }
  else if ( rf_entity_class_flags724_has_mask800(*a1) )
  {
    sub_40EAB0(*(_DWORD *)(*a1 + 44));
    rf_timestamp_arm_random_inclusive_milliseconds(a1 + 141, 3000, 8000);
    a1[332] |= 8u;
    return rf_ai_secondary_state_write((int)a1, 11);
  }
  else
  {
    v8 = rf_entity_resolve_handle(a1[176]);
    if ( v8 && *(_DWORD *)(v8 + 5168) && !sub_4024E0(v8, *a1) )
    {
      return rf_timestamp_arm_random_inclusive_milliseconds(a1 + 141, 200, 500);
    }
    else
    {
      v7 = rf_object_resolve_handle(a1[176]);
      if ( !v7 )
        goto LABEL_23;
      v4 = 0;
      rf_vector3_default_construct_noop(v2);
      v3 = 0.0;
      while ( v3 < 9.0 && v4 < 4 )
      {
        sub_40EAB0(*(_DWORD *)(*a1 + 44));
        v3 = rf_point_segment_residual_squared_xy_projection(
               (const float *)(v7 + 60),
               (const float *)a1 + 193,
               (const float *)a1 + 224,
               v2);
        ++v4;
      }
      if ( v4 == 4 && v3 < 9.0 )
      {
        return rf_ai_route_reset((int)(a1 + 186));
      }
      else
      {
LABEL_23:
        if ( rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(*a1 + 44), a1[1]) )
          rf_entity_stop_weapon_firing(*(_DWORD *)(*a1 + 44), a1[1]);
        v6 = rand() % 1000;
        rf_replicator_arm_milliseconds(a1 + 141, v6 + 300);
        a1[332] |= 8u;
        return rf_ai_secondary_state_write((int)a1, 11);
      }
    }
  }
}

