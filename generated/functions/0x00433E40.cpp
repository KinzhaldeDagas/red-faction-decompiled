// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00433E40 rf_entity_arm_secondary_retry_and_feedback
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(entity pointer), incidental EAX/AL. FIRST arm embedded entity+1212 deadline500ms relative to wrapped clock, then player-associated438AC0.
// ANYnonzero AL invokes nonpositional gamesound(event2,DWORD0,FLOAT0,FLOAT1), returns its EAX unchanged; zero returns predicate residue withAL0. No own entity NULL guard,
// ammo/ownership/dead test, body action, projectile or caller-status conversion. Timer mutation occurs even if no player association or sound allocation fails.
char __cdecl rf_entity_arm_secondary_retry_and_feedback(int a1)
{
  char result; // al

  rf_replicator_arm_milliseconds((int *)(a1 + 1212), 500);
  result = sub_438AC0(a1);
  if ( result )
    return rf_gamesound_play_event(2, 0, 0.0, 1.0);
  return result;
}

