// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503030 rf_mission_event_registry_find_saved_uid_for_death
// UNREALRED VERIFIED [event-lifecycle-20261028]: Linear scan of event registry0x90B0E0; compares each event dword E+36 against caller UID and returns first match, else0. Same behavior as0x4F7720 but distinct executable function; called by entity death-completion and0x4485C0. Registry count reread every iteration.
int __cdecl rf_mission_event_registry_find_saved_uid_for_death(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_90B0E0); ++i )
  {
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(unk_90B0E0, i) + 36) == a1 )
      return *(_DWORD *)sub_552200(unk_90B0E0, i);
  }
  return 0;
}

