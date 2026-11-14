// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FAA80 rf_event_create_goal_set_record
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Create event37 Goal_Set then copy supplied string object to event+0x2B8. Does not create named goal records or change their counts until runtime forward/reverse.
int __cdecl rf_event_create_goal_set_record(float *a1, int a2)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_mission_event_create_at_position(a1, 0x25u);
  if ( v3 )
    rf_string_assign_from_object((_DWORD *)(v3 + 696), a2);
  return v3;
}

