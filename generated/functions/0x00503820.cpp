// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503820 rf_event_goal_set_construct
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] Common constructor, install event_goal_set vtable0x63E230, construct name string+0x2B8. No creation of shared/level goal records or counter mutation in this body.
int __thiscall rf_event_goal_set_construct(int this)
{
  rf_mission_event_construct_base((char *)this);
  *(_DWORD *)this = &event_goal_set::`vftable';
  rf_string_construct_empty((_DWORD *)(this + 696));
  return this;
}

