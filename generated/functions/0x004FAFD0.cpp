// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FAFD0 rf_event_endgame_create_from_fields
// UNREALRED VERIFIED [event-builders-20261028]: Creates subtype71 (Endgame) at caller position through rf_mission_event_create_at_position; returns event E or0. Returns common event-creation result directly; no extra field stores. Common object base is E+4; offsets here are from E.
int __cdecl rf_event_endgame_create_from_fields(float *a1)
{
  return rf_mission_event_create_at_position(a1, 0x47u);
}

