// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7620 rf_mission_event_activate_by_uid
// UNREALRED VERIFIED [event-registry-crc-20261028]: Resolves UID through rf_mission_event_find_by_uid; if nonnull calls rf_mission_event_activate(event,arg2,arg3,1). Missing event returns null/zero. Does not enumerate or dispatch non-event objects.
int *__cdecl rf_mission_event_activate_by_uid(int a1, int a2, int a3)
{
  int *result; // eax

  result = (int *)rf_mission_event_find_by_uid(a1);
  if ( result )
    return (int *)rf_mission_event_activate(result, a2, a3, 1);
  return result;
}

