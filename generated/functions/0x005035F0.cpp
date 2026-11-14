// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005035F0 rf_event_set_light_state_construct
// UNREALRED VERIFIED [event-builders-20261028]: Calls rf_mission_event_construct_base(this), then installs RTTI-backed event_set_light_state vtable. No explicit initialization of added derived payload fields in this body; field builders initialize them separately. Returns this. Constructor alone does not trigger event activation.
char *__thiscall rf_event_set_light_state_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_set_light_state::`vftable';
  return this;
}

