// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA3C0 rf_event_shake_player_create_from_fields
// UNREALRED VERIFIED [event-builders-20261028]: Creates subtype18 (Shake_Player) at caller position through rf_mission_event_create_at_position; returns event E or0. Derived stores occur only when creation succeeds. Stores two supplied floats at E+696 and E+700, in argument order. Common object base is E+4; offsets here are from E.
int __cdecl rf_event_shake_player_create_from_fields(float *a1, float a2, float a3)
{
  int v4; // [esp+0h] [ebp-4h]

  v4 = rf_mission_event_create_at_position(a1, 0x12u);
  if ( v4 )
  {
    *(float *)(v4 + 696) = a2;
    *(float *)(v4 + 700) = a3;
  }
  return v4;
}

