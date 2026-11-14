// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503370 rf_event_when_dead_construct
// UNREALRED VERIFIED [mission-event-when-dead]: Constructs the base event object and installs event_when_dead::vftable.
char *__thiscall rf_event_when_dead_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_when_dead::`vftable';
  return this;
}

