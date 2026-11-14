// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FAD60 rf_event_alarm_siren_create_from_fields
// UNREALRED VERIFIED [event-builders-20261028]: Creates subtype45 (Alarm_Siren) at caller position through rf_mission_event_create_at_position; returns event E or0. Derived stores occur only when creation succeeds. Clears runtime byte E+696 to0; no other derived-field assignment in this body. Common object base is E+4; offsets here are from E.
int __cdecl rf_event_alarm_siren_create_from_fields(float *a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_mission_event_create_at_position(a1, 0x2Du);
  if ( v2 )
    *(_BYTE *)(v2 + 696) = 0;
  return v2;
}

