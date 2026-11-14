// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F5F00 rf_snapshot_pack_replicator_remaining
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] If deadline is armed per rf_replicator_is_armed, store signed wrapped remaining milliseconds from0x55F0B0; otherwise store-1. Does not store absolute game-clock deadline. Since-1 is also possible as signed remaining value, the representation itself does not distinguish a deadline exactly1ms overdue from disarmed sentinel.
int __cdecl rf_snapshot_pack_replicator_remaining(int *a1, int *a2)
{
  int result; // eax

  result = rf_replicator_is_armed(a1);
  if ( (_BYTE)result )
  {
    result = rf_replicator_signed_remaining_milliseconds(a1);
    *a2 = result;
  }
  else
  {
    *a2 = -1;
  }
  return result;
}

