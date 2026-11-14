// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00504060 rf_mission_event_destroy_two_strings_704_712
// UNREALRED VERIFIED [event-lifecycle-20261028]: Uses exception-aware vector destructor for two8-byte RF strings at E+704 and E+712, then destroys base event members. Does not free E storage. Name describes shared member layout rather than asserting a unique subclass.
void __thiscall rf_mission_event_destroy_two_strings_704_712(char *this)
{
  `eh vector destructor iterator'(this + 704, 8u, 2, rf_string_destroy_buffer);
  rf_mission_event_destroy_base_members((void **)this);
}

