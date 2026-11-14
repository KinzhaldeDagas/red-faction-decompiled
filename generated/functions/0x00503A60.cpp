// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503A60 rf_event_modify_rotating_mover_construct
// UNREALRED VERIFIED [event-lifecycle-20261028]: Calls rf_mission_event_construct_base(E), installs RTTI-backed event_modify_rotating_mover vtable. No extra derived-payload initialization in this body. Other derived scalar fields are not explicitly initialized here. Returns E; does not activate event.
char *__thiscall rf_event_modify_rotating_mover_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_modify_rotating_mover::`vftable';
  return this;
}

