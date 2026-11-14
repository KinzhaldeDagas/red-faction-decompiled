// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503A40 rf_event_skybox_state_construct
// UNREALRED VERIFIED [authored-sky-renderer] Constructs the type-59 Skybox_State object by installing event_skybox_state's vtable after the common mission-event base constructor.
char *__thiscall rf_event_skybox_state_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_skybox_state::`vftable';
  return this;
}

