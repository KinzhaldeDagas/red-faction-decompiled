// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00406800 rf_ai_mode6_route_to_stored_destination
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, central mode6 handler. Walk predicate435440 any-nonzero and fall/airborne AL0 call4355A0
// movement reset, ignoring result. If secondary+692!=1 AND deadline+560 elapsed EXACT1: route-build(owner handle,block vector+1100); only EXACT AL1 writes secondary1. Every other AL
// calls40A2A0 and returns before scan. Re-reads secondary: ==1 calls route-update(route+744,extra0); EXACT EAX==-2 invokes409950(block) and skips weighted scan. Every other route
// result (including-1) or secondary state invokes404740 scan-and-commit. No own deadline rearm, direct target clear, destination copy, current route validity or uniform return
// boolean.
void __cdecl rf_ai_mode6_route_to_stored_destination(int *a1)
{
  if ( rf_entity_class_flags724_has_mask1(*a1) && !rf_entity_uses_fall_or_airborne_vehicle_motion(*a1) )
    sub_4355A0(*a1);
  if ( a1[173] != 1 && rf_replicator_has_elapsed(a1 + 140) )
  {
    if ( rf_ai_route_build(*(_DWORD *)(*a1 + 44), (int)(a1 + 275)) != 1 )
    {
      sub_40A2A0(a1);
      return;
    }
    rf_ai_secondary_state_write((int)a1, 1);
  }
  if ( a1[173] == 1 && rf_ai_route_update((int)(a1 + 186)) == -2 )
    sub_409950(a1);
  else
    rf_ai_scan_and_commit_weighted_target(a1);
}

