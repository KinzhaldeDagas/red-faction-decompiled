// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA790 rf_event_create_follow_waypoints_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event28 Follow_Waypoints. Resolve supplied second C string through0x487370 to event dword+0x2B8; copy first source C string into event string+0x2BC; store two raw byte arguments+0x2C4/+0x2C5. No resolution-result validation, route install, numeric mode write or bool normalization at creation.
int __cdecl rf_event_create_follow_waypoints_record(float *a1, char *Source, char *String1, char a4, char a5)
{
  int v6; // [esp+0h] [ebp-4h]

  v6 = rf_mission_event_create_at_position(a1, 0x1Cu);
  if ( v6 )
  {
    *(_DWORD *)(v6 + 696) = sub_487370(String1);
    rf_string_assign_from_cstr((_DWORD *)(v6 + 700), Source);
    *(_BYTE *)(v6 + 708) = a4;
    *(_BYTE *)(v6 + 709) = a5;
  }
  return v6;
}

