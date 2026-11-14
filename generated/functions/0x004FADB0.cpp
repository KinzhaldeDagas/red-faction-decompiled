// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FADB0 rf_event_monitor_state_create_from_fields
// UNREALRED VERIFIED [event-builders-20261028]: Creates subtype49 (Monitor_State) at caller position through rf_mission_event_create_at_position; returns event E or0. Derived stores occur only when creation succeeds. Arguments after position are dword, byte, float; stores float at E+696, dword at E+700, byte at E+704. Common object base is E+4; offsets here are from E.
int __cdecl rf_event_monitor_state_create_from_fields(float *a1, int a2, char a3, float a4)
{
  int v5; // [esp+0h] [ebp-4h]

  v5 = rf_mission_event_create_at_position(a1, 0x31u);
  if ( v5 )
  {
    *(float *)(v5 + 696) = a4;
    *(_DWORD *)(v5 + 700) = a2;
    *(_BYTE *)(v5 + 704) = a3;
  }
  return v5;
}

