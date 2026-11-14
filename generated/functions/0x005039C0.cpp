// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005039C0 rf_event_alarm_construct
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Call common mission-event constructor then install event_alarm vtable0x63E2D0. No extra field initialization in this body; global alarm state is maintained separately.
char *__thiscall rf_event_alarm_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_alarm::`vftable';
  return this;
}

