// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F9FF0 rf_event_goto_player_create_from_fields
// UNREALRED VERIFIED [event-builders-20261028]: Creates subtype6 (Goto_Player) at caller position through rf_mission_event_create_at_position; returns event E or0. Derived stores occur only when creation succeeds. Stores supplied byte at E+696 without boolean normalization. Common object base is E+4; offsets here are from E.
int __cdecl rf_event_goto_player_create_from_fields(float *a1, char a2)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_mission_event_create_at_position(a1, 6u);
  if ( v3 )
    *(_BYTE *)(v3 + 696) = a2;
  return v3;
}

