// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00409B90 rf_ai_probe_target_route_mode12_with_backoff
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Target full handle+704 must resolve as ENTITY; then block deadline+572 must have elapsed EXACT AL1. Calls40EBF0(owner
// handle+44,target COMMON position+60). EXACT AL1: mode12(-1,-1), secondary1, rearm SAME deadline6000ms. Every other AL rearms1000ms without mode/state writes. Missing target or
// nonelapsed timer leaves deadline untouched. Does not store target point, query collision directly, reset route here or independently construct success boolean.
char __cdecl rf_ai_probe_target_route_mode12_with_backoff(int *a1)
{
  int v1; // eax
  int v3; // [esp+0h] [ebp-4h]

  v1 = rf_entity_resolve_handle(a1[176]);
  v3 = v1;
  if ( v1 )
  {
    LOBYTE(v1) = rf_replicator_has_elapsed(a1 + 143);
    if ( (unsigned __int8)v1 == 1 )
    {
      if ( rf_ai_build_avoid_route_with_default_parameter(*(_DWORD *)(*a1 + 44), v3 + 60) == 1 )
      {
        rf_ai_numeric_mode_write(a1, 12, -1, -1);
        rf_ai_secondary_state_write((int)a1, 1);
        LOBYTE(v1) = rf_replicator_arm_milliseconds(a1 + 143, 6000);
      }
      else
      {
        LOBYTE(v1) = rf_replicator_arm_milliseconds(a1 + 143, 1000);
      }
    }
  }
  return v1;
}

