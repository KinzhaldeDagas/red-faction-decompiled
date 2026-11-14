// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503CA0 rf_mission_event_construct_base
// UNREALRED VERIFIED [mission-event-runtime]: Constructs the base event object, installs event::vftable, and initializes its delayed-activation replicator.
char *__thiscall rf_mission_event_construct_base(char *this)
{
  rf_common_object_construct_members(this + 4);
  *(_DWORD *)this = &event::`vftable';
  rf_timestamp4_construct_invalid((int *)this + 166);
  rf_dword_array_construct_capacity(this + 668, 0);
  return this;
}

