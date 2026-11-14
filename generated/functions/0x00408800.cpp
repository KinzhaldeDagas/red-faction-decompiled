// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00408800 rf_ai_target_needs_route_approach
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, explicit AL0/1. DWORD+1184==2, reload predicate EXACT1,
// unholster-animation-deadline-active EXACT1 or crouch EXACT1 each returns0. Resolve COMMON target+704; missing returns0. Source current descriptor POINTER equals registry
// lookup445740(1) AND secondary+692==3 ->copy target common position but replace Y with owner common.Y; other cases use full common position. Distance is Euclidean roundedfloat32.
// Independently resolve target handle as ENTITY; nonnull and contact-geomod-class-flag400 predicate EXACT1 subtracts DOUBLE3 and roundsfloat32, with no nonnegative clamp. Maximum
// attack range4098B0 roundsfloat32; secondary2 multiplies it byDOUBLE1.5 and roundsfloat32. Ordered range<adjusted distance returns1. Equal/greater/UNORDERED comparison reaches
// fallback: return1 ONLY when BYTE block+668==0 AND BYTE+669==0 AND block deadline+568 elapsed EXACT1; otherwise0. Thus NaN may still return1 through probe-byte/timer fallback. No
// state writes, own owner-death test, target health/type constraint or actual route construction.
bool __cdecl rf_ai_target_needs_route_approach(int *a1)
{
  int v2; // esi
  float v3[3]; // [esp+4h] [ebp-20h] BYREF
  float v4; // [esp+10h] [ebp-14h]
  float v5; // [esp+14h] [ebp-10h]
  int v6; // [esp+18h] [ebp-Ch]
  bool v7; // [esp+1Fh] [ebp-5h]
  int v8; // [esp+20h] [ebp-4h]

  if ( a1[296] == 2 )
    return 0;
  if ( rf_entity_reload_in_progress(*a1) )
    return 0;
  if ( rf_ai_unholster_animation_deadline_active((int)a1) )
    return 0;
  if ( rf_entity_is_crouched_state810(*a1) )
    return 0;
  v6 = rf_object_resolve_handle(a1[176]);
  if ( !v6 )
    return 0;
  v2 = *a1;
  v7 = *(_DWORD *)(v2 + 2136) == (_DWORD)sub_445740(1u);
  rf_vector3_copy_return_destination(v3, (float *)(v6 + 60));
  if ( v7 && a1[173] == 3 )
    v3[1] = *(float *)(*a1 + 64);
  v4 = rf_vector_distance((const float *)(*a1 + 60), v3);
  v8 = rf_entity_resolve_handle(a1[176]);
  if ( v8 && rf_entity_class_has_contact_geomod_flag400(v8) )
    v4 = v4 - 3.0;
  v5 = rf_ai_resolve_maximum_attack_range(a1);
  if ( a1[173] == 2 )
    v5 = v5 * 1.5;
  if ( v5 < (double)v4 )
    return 1;
  return !*((_BYTE *)a1 + 668) && !*((_BYTE *)a1 + 669) && rf_replicator_has_elapsed(a1 + 142);
}

