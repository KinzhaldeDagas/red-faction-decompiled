// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502000 rf_mission_event_set_disabled_flag
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] OR enclosing event flags+0x2B0 mask0x1. rf_mission_event_activate uses this bit to skip local handler/delay admission, but still stores supplied context first. No timer reset, target propagation or autonomous-update latch reset in this setter.
int __cdecl rf_mission_event_set_disabled_flag(int a1)
{
  *(_DWORD *)(a1 + 688) |= 1u;
  return a1;
}

