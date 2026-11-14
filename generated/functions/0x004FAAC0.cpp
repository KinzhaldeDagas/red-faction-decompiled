// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FAAC0 rf_event_create_goal_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event35 Goal_Create. Store supplied initial dword+0x2B8, current dword+0x2C0=same, and raw shared-record byte+0x2C4. ONLY byte==1 attempts shared-name registration0x4FAB50(name,initial,current), then independently looks up that name and copies existing shared count+0xC to current+0x2C0. Existing shared record can override supplied initial current count. No threshold activation, key copy into common event name, or lower clamp in this routine.
int __cdecl rf_event_create_goal_record(float *a1, int a2, char a3, char *String2)
{
  int shared_record_by_name; // [esp+0h] [ebp-8h]
  int v6; // [esp+4h] [ebp-4h]

  v6 = rf_mission_event_create_at_position(a1, 0x23u);
  if ( v6 )
  {
    *(_DWORD *)(v6 + 696) = a2;
    *(_BYTE *)(v6 + 708) = a3;
    *(_DWORD *)(v6 + 704) = a2;
    if ( a3 == 1 )
    {
      rf_goal_register_shared_record_if_missing(String2, a2, *(_DWORD *)(v6 + 704));
      shared_record_by_name = rf_goal_find_shared_record_by_name(String2);
      if ( shared_record_by_name )
        *(_DWORD *)(v6 + 704) = *(_DWORD *)(shared_record_by_name + 12);
    }
  }
  return v6;
}

