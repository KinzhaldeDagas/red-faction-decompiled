// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7720 rf_mission_event_registry_find_by_saved_uid
// UNREALRED VERIFIED [event-registry-crc-20261028]: Linear scan of registry0x90B0E0; returns first event E whose dword E+36 equals input saved UID, or0. Unlike rf_mission_event_find_by_uid, does not use runtime object resolver or recheck common type6. Count reread each iteration.
int __cdecl rf_mission_event_registry_find_by_saved_uid(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_90B0E0); ++i )
  {
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(unk_90B0E0, i) + 36) == a1 )
      return *(_DWORD *)sub_552200(unk_90B0E0, i);
  }
  return 0;
}

