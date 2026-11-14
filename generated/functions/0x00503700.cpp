// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503700 rf_event_set_ai_mode_construct
// UNREALRED VERIFIED [ai-set-mode-event-20260826]: Constructs event_set_ai_mode after the common mission-event base and installs its vtable at 0x63E1D0; dispatch slot 0x63E1E4 points to rf_event_set_ai_mode_dispatch.
char *__thiscall rf_event_set_ai_mode_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_set_ai_mode::`vftable';
  return this;
}

