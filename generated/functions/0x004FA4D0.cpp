// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA4D0 rf_event_create_switch_model_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event21 Switch_Model then copy supplied string object to event string+0x2B8. No per-target definition resolution, model release or compatibility test at creation.
int __cdecl rf_event_create_switch_model_record(float *a1, int a2)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_mission_event_create_at_position(a1, 0x15u);
  if ( v3 )
    rf_string_assign_from_object((_DWORD *)(v3 + 696), a2);
  return v3;
}

