// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503C80 rf_event_when_armor_reaches_construct
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] Common mission-event constructor then install event_when_armor_reaches vtable0x63E424. No explicit latch+0x2B8 or integer threshold+0x2BC initialization here.
char *__thiscall rf_event_when_armor_reaches_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_when_armor_reaches::`vftable';
  return this;
}

