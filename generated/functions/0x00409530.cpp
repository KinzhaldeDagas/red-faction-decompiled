// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00409530 rf_ai_update_unholster_deadlines
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Deadline+628 elapsed EXACT AL1 AND flags+1328 mask0x100 set ->arm deadline+536 with250ms, then clear mask0x100. Does
// NOT reset deadline+628. Independently tests deadline+632 elapsed EXACT1; on true resets that deadline and clears mask0x200 regardless of whether already set. Second path does not
// require first path, a live owner, mode or animation. Timers use wrapped game milliseconds, not raw tick/unknown units. EAX is block pointer on second-path success, otherwise timer
// helper result; no uniform status.
int *__cdecl rf_ai_update_unholster_deadlines(int *a1)
{
  int *result; // eax

  if ( rf_replicator_has_elapsed(a1 + 157) && (a1[332] & 0x100) != 0 )
  {
    rf_replicator_arm_milliseconds(a1 + 134, 250);
    a1[332] &= ~0x100u;
  }
  result = (int *)rf_replicator_has_elapsed(a1 + 158);
  if ( (unsigned __int8)result == 1 )
  {
    rf_replicator_reset(a1 + 158);
    a1[332] &= ~0x200u;
    return a1;
  }
  return result;
}

