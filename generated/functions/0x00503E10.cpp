// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503E10 rf_mission_event_scalar_delete_string_704
// UNREALRED VERIFIED [event-lifecycle-20261028]: Calls member destructor0x00504000(E). Calls operator delete(E) only when low flags byte bit0 is set; otherwise destroys members and retains allocation. Returns original E address (may be freed). No array-delete semantics or other flag-bit handling here.
void *__thiscall rf_mission_event_scalar_delete_string_704(void *this, char a2)
{
  rf_mission_event_destroy_string_704((int)this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

