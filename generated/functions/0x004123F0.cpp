// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004123F0 rf_entity_set_player_linked_perturbation_timer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, push-region/GeoMod/use-selector/physics batch chains, original float constants and field widths and native
// signed/x87/stack/callback ABI): Cdecl(required link object,perturbation float,duration seconds float). Resolves entity handle at *(*(link+4)+20); link and intermediate pointer have
// no null guard, unresolved entity returns without writes. Resolved entity receives FLOAT+2232=duration, deadline+2236 armed with LOW32 truncation-toward-zero(duration*DOUBLE1000),
// then FLOAT+2228=perturbation. Does not normalize/clamp duration or perturbation. EAX is resolverNULL on miss or incidental arm-helper return on hit. Push-region caller supplies
// perturbation and FLOAT0.05. Field name describes the observed caller and stores without assigning an unverified camera/shake consumer.
int __cdecl rf_entity_set_player_linked_perturbation_timer(int a1, float a2, float a3)
{
  int result; // eax
  int v4; // [esp+0h] [ebp-4h]

  result = rf_entity_resolve_handle(*(_DWORD *)(*(_DWORD *)(a1 + 4) + 20));
  v4 = result;
  if ( result )
  {
    *(float *)(result + 2232) = a3;
    result = rf_replicator_arm_milliseconds((int *)(result + 2236), (int)(a3 * 1000.0));
    *(float *)(v4 + 2228) = a2;
  }
  return result;
}

