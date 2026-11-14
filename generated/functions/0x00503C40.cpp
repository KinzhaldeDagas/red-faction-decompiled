// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503C40 rf_event_when_countdown_reaches_construct
// UNREALRED VERIFIED [event-lifecycle-20261028]: Calls rf_mission_event_construct_base(E), installs RTTI-backed event_when_countdown_reaches vtable. No extra derived-payload initialization in this body. Other derived scalar fields are not explicitly initialized here. Returns E; does not activate event.
char *__thiscall rf_event_when_countdown_reaches_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_when_countdown_reaches::`vftable';
  return this;
}

