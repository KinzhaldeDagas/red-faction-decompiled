// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503E40 rf_mission_event_scalar_delete_two_strings_704_712
// UNREALRED VERIFIED [event-lifecycle-20261028]: Calls member destructor0x00504060(E). Calls operator delete(E) only when low flags byte bit0 is set; otherwise destroys members and retains allocation. Returns original E address (may be freed). No array-delete semantics or other flag-bit handling here.
char *__thiscall rf_mission_event_scalar_delete_two_strings_704_712(char *this, char a2)
{
  rf_mission_event_destroy_two_strings_704_712(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

