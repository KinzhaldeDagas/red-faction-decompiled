// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA050 rf_event_shoot_once_create_from_fields
// UNREALRED VERIFIED [event-builders-20261028]: Creates subtype9 (Shoot_Once) at caller position through rf_mission_event_create_at_position; returns event E or0. Derived stores occur only when creation succeeds. Stores supplied dword at E+696. Common object base is E+4; offsets here are from E.
int __cdecl rf_event_shoot_once_create_from_fields(float *a1, int a2)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_mission_event_create_at_position(a1, 9u);
  if ( v3 )
    *(_DWORD *)(v3 + 696) = a2;
  return v3;
}

