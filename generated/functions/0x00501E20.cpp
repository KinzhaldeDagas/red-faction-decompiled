// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501E20 rf_mission_event_type_from_name
// UNREALRED VERIFIED [mission-event-runtime]: Case-insensitively resolves an authored event class name through the exact 90-entry retail event-type table and returns -1 when absent.
int __cdecl rf_mission_event_type_from_name(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 90; ++i )
  {
    if ( rf_string_equals_case_insensitive(a1, (char *)rf_mission_event_type_names[i]) )
      return i;
  }
  return -1;
}

