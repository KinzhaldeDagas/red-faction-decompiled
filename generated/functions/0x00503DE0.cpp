// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503DE0 rf_mission_event_scalar_delete_string_696
// UNREALRED VERIFIED [event-lifecycle-20261028]: Calls member destructor0x00503FA0(E). Calls operator delete(E) only when low flags byte bit0 is set; otherwise destroys members and retains allocation. Returns original E address (may be freed). No array-delete semantics or other flag-bit handling here.
void *__thiscall rf_mission_event_scalar_delete_string_696(void *this, char a2)
{
  rf_mission_event_destroy_string_696((int)this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

