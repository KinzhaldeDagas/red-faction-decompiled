// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503140 rf_event_goto_construct
// UNREALRED VERIFIED [ai-goto-event-20260826]: Constructs event_goto after the common mission-event base and installs vtable 0x63E014; slot +4 points to rf_event_goto_dispatch and slot +8 uses generic reverse dispatch.
char *__thiscall rf_event_goto_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_goto::`vftable';
  return this;
}

