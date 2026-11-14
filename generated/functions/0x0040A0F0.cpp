// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040A0F0 rf_ai_reset_route_and_retry_target_approach
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. ALWAYS resets route+744 before resolving COMMON target+704. Missing ->40A2A0(block), then guarded target
// helper40BA80(block,-1); no unconditional raw target write. Found ->seven-arg segment query(owner COMMON+60,target COMMON+60,FLOAT1.2999999523162842,3,owner,target,NULL); only EXACT
// AL1 stops. Other AL calls40DF30(owner handle,target COMMON+60); AL0 additionally invokes40ABE0(block). No own mode/state assignment, deadline arm or uniform return boolean.
char __cdecl rf_ai_reset_route_and_retry_target_approach(int *a1)
{
  char result; // al
  int v2; // [esp+14h] [ebp-8h]

  rf_ai_route_reset((int)(a1 + 186));
  v2 = rf_object_resolve_handle(a1[176]);
  if ( v2 )
  {
    result = rf_segment_objects_or_world_hit_filtered_by_radius(*a1 + 60, v2 + 60, 1.3, 3, *a1, v2, 0);
    if ( result != 1 )
    {
      result = rf_ai_build_avoid_route_with_target_adjustment(*(_DWORD *)(*a1 + 44), v2 + 60);
      if ( !result )
        return rf_ai_selected_weapon_projectile_retarget_or_delay(a1);
    }
  }
  else
  {
    sub_40A2A0(a1);
    return sub_40BA80(a1, -1);
  }
  return result;
}

