// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FAD30 rf_event_music_stop_create_from_fields
// UNREALRED VERIFIED [event-builders-20261028]: Creates subtype42 (Music_Stop) at caller position through rf_mission_event_create_at_position; returns event E or0. Derived stores occur only when creation succeeds. Stores supplied float at E+696. Common object base is E+4; offsets here are from E.
int __cdecl rf_event_music_stop_create_from_fields(float *a1, float a2)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_mission_event_create_at_position(a1, 0x2Au);
  if ( v3 )
    *(float *)(v3 + 696) = a2;
  return v3;
}

