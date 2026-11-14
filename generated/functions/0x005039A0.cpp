// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005039A0 rf_event_alarm_siren_construct
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] Construct event_alarm_siren: common mission-event constructor then vtable 0x63E2BC. No explicit initialization of siren active byte +0x2B8 or voice +0x2BC in this body.
char *__thiscall rf_event_alarm_siren_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_alarm_siren::`vftable';
  return this;
}

