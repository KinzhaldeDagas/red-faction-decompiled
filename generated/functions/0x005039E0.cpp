// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005039E0 rf_event_monitor_state_construct
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Call common mission-event constructor then install event_monitor_state vtable0x63E2E4. No explicit initialization of event+0x2B8/+0x2BC/+0x2C0 in this body.
char *__thiscall rf_event_monitor_state_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_monitor_state::`vftable';
  return this;
}

