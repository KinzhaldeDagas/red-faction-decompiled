// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FACF0 rf_event_music_start_create_from_fields
// UNREALRED VERIFIED [event-builders-20261028]: Creates subtype41 (Music_Start) at caller position through rf_mission_event_create_at_position; returns event E or0. Derived stores occur only when creation succeeds. Assigns caller C string into RF string subobject at E+696 via0x55FFA0 and stores supplied byte at E+704. Common object base is E+4; offsets here are from E.
int __cdecl rf_event_music_start_create_from_fields(float *a1, char *Source, char a3)
{
  int v4; // [esp+0h] [ebp-4h]

  v4 = rf_mission_event_create_at_position(a1, 0x29u);
  if ( v4 )
  {
    rf_string_assign_from_cstr((_DWORD *)(v4 + 696), Source);
    *(_BYTE *)(v4 + 704) = a3;
  }
  return v4;
}

