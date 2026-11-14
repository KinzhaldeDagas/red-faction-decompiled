// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005037B0 rf_event_goal_check_construct
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] Common constructor, install event_goal_check vtable0x63E21C, construct name string+0x2B8. No explicit threshold+0x2C0 initialization in this body.
int __thiscall rf_event_goal_check_construct(int this)
{
  rf_mission_event_construct_base((char *)this);
  *(_DWORD *)this = &event_goal_check::`vftable';
  rf_string_construct_empty((_DWORD *)(this + 696));
  return this;
}

