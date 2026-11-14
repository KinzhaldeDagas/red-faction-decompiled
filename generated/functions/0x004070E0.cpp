// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004070E0 rf_ai_mode4_route_and_target_scan_update
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, central mode4 handler. Secondary+692!=1 and deadline+560 elapsed EXACT1 ->40DCA0(owner
// handle); EXACT AL1 writes secondary1, other AL arms+560 for1000ms and resets route+744. Does not return on that failure: continues remaining checks. Re-reads secondary; ==1 calls
// route-update(route+744,extra0), ignores result. Speech/body-action predicate EXACT1 and fast length(block vector+1280) ordered>DOUBLE0.10000000149011612 resets owner model actions,
// no model-null guard. Finally deadline+732 elapsed any-nonzero: secondary12 clears AI flags+1328 mask0x00800000; then only mask clear, replacement-target predicate404AC0==EXACT1 and
// signed primary selected index+4>=0 invoke404740 weighted scan. No independent scan-deadline rearm on suppressed branches, numeric mode write, dead/authority gate or uniform return
// boolean.
char __cdecl rf_ai_mode4_route_and_target_scan_update(int *a1)
{
  char result; // al

  if ( a1[173] != 1 && rf_replicator_has_elapsed(a1 + 140) )
  {
    if ( sub_40DCA0(*(_DWORD *)(*a1 + 44)) == 1 )
    {
      rf_ai_secondary_state_write((int)a1, 1);
    }
    else
    {
      rf_replicator_arm_milliseconds(a1 + 140, 1000);
      rf_ai_route_reset((int)(a1 + 186));
    }
  }
  if ( a1[173] == 1 )
    rf_ai_route_update((int)(a1 + 186));
  if ( rf_entity_admits_speech_body_actions(*a1) && rf_vector_fast_length((float *)a1 + 320) > 0.1000000014901161 )
    rf_model_handle_reset_actions_adapter(*(_DWORD *)(*a1 + 128));
  result = rf_replicator_has_elapsed(a1 + 183);
  if ( result )
  {
    if ( a1[173] == 12 )
      a1[332] &= ~0x800000u;
    result = (char)a1;
    if ( ((unsigned int)&unk_800000 & a1[332]) == 0 )
    {
      result = rf_ai_should_seek_replacement_target(a1);
      if ( result == 1 && a1[1] >= 0 )
        return rf_ai_scan_and_commit_weighted_target(a1);
    }
  }
  return result;
}

