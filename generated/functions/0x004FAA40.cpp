// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FAA40 rf_event_create_goal_check_record
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Create event36 Goal_Check; copy supplied string object to name field+0x2B8 and raw signed threshold dword+0x2C0. No shared-goal registration, goal count mutation or runtime comparison here.
int __cdecl rf_event_create_goal_check_record(float *a1, int a2, int a3)
{
  int v4; // [esp+0h] [ebp-4h]

  v4 = rf_mission_event_create_at_position(a1, 0x24u);
  if ( v4 )
  {
    rf_string_assign_from_object((_DWORD *)(v4 + 696), a2);
    *(_DWORD *)(v4 + 704) = a3;
  }
  return v4;
}

