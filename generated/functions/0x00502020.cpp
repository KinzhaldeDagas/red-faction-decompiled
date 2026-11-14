// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502020 rf_mission_event_clear_disabled_flag
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Clear enclosing event flags+0x2B0 mask0x1 only. Does not itself activate event, arm delay, clear one-shot latches or invoke targets.
int __cdecl rf_mission_event_clear_disabled_flag(int a1)
{
  *(_DWORD *)(a1 + 688) &= ~1u;
  return a1;
}

