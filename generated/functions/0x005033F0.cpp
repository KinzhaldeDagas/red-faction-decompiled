// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005033F0 rf_event_cyclic_timer_construct
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] Common mission-event constructor, install event_cyclic_timer vtable0x63E12C, construct embedded Replicator+0x2C8. No explicit initial interval, enabled/repeat byte, limit or accumulated count assignment in this body.
char *__thiscall rf_event_cyclic_timer_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_cyclic_timer::`vftable';
  rf_timestamp4_construct_invalid((int *)this + 178);
  return this;
}

