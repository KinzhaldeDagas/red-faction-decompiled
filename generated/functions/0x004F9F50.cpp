// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F9F50 rf_event_slay_create_from_fields
// UNREALRED VERIFIED [event-builders-20261028]: Creates subtype1 (Slay_Object) at caller position through rf_mission_event_create_at_position; returns event E or0. Derived stores occur only when creation succeeds. Resolves caller action-name string through rf_body_action_find_canonical_index and stores resulting index dword at E+696; no success/range test on that index. Common object base is E+4; offsets here are from E.
int __cdecl rf_event_slay_create_from_fields(float *a1, char *String1)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_mission_event_create_at_position(a1, 1u);
  if ( v3 )
    *(_DWORD *)(v3 + 696) = rf_body_action_find_canonical_index(String1);
  return v3;
}

