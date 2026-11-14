// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA250 rf_event_shield_create_from_fields
// UNREALRED VERIFIED [event-builders-20261028]: Creates subtype14 (Armor) at caller position through rf_mission_event_create_at_position; returns event E or0. Derived stores occur only when creation succeeds. Retail name Armor; RTTI class event_shield. Stores supplied dword at E+696 and byte at E+700 without clamp or normalization. Common object base is E+4; offsets here are from E.
int __cdecl rf_event_shield_create_from_fields(float *a1, int a2, char a3)
{
  int v4; // [esp+0h] [ebp-4h]

  v4 = rf_mission_event_create_at_position(a1, 0xEu);
  if ( v4 )
  {
    *(_DWORD *)(v4 + 696) = a2;
    *(_BYTE *)(v4 + 700) = a3;
  }
  return v4;
}

