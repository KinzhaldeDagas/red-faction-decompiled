// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503120 rf_event_slay_construct
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Call common mission-event constructor then install event_slay vtable0x63E000. No explicit initialization of event raw field+0x2B8 copied to entity+0x83C by forward callback.
char *__thiscall rf_event_slay_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_slay::`vftable';
  return this;
}

