// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503A80 rf_event_go_undercover_construct
// UNREALRED VERIFIED [event-builders-20261028]: Calls rf_mission_event_construct_base(this), then installs RTTI-backed event_go_undercover vtable. No explicit initialization of added derived payload fields in this body; field builders initialize them separately. Returns this. Constructor alone does not trigger event activation.
char *__thiscall rf_event_go_undercover_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_go_undercover::`vftable';
  return this;
}

