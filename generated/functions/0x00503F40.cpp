// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503F40 rf_mission_event_destroy_string_700
// UNREALRED VERIFIED [event-lifecycle-20261028]: Destroys RF string at E+700 then base event members. Does not free E storage. Name describes shared member layout rather than asserting a unique subclass.
void __thiscall rf_mission_event_destroy_string_700(void **this)
{
  rf_string_destroy_buffer(this + 175);
  rf_mission_event_destroy_base_members(this);
}

