// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005040D0 rf_mission_event_destroy_base_only
// UNREALRED VERIFIED [event-lifecycle-20261028]: Delegates only to base event member destructor0x503D20. Does not free E storage. Name describes shared member layout rather than asserting a unique subclass.
void __thiscall rf_mission_event_destroy_base_only(void **this)
{
  rf_mission_event_destroy_base_members(this);
}

