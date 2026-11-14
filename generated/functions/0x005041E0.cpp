// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005041E0 rf_trigger_has_direct_load_to_different_level
// UNREALRED VERIFIED [trigger-airlock-20261022] Examines direct linked common type6 event type22 Load_Level. Returns true when destination differs from current logical level name using560A00 case-insensitive NOT-EQUAL predicate. This flag suppresses direct mover dispatch during delayed airlock completion; not a recursive event-graph search.
// UNREALRED VERIFIED [event-lifecycle-20261028]: Scans UID links in trigger+724 pointer-array; resolves each event and returns true if subtype at E+656 is22 Load_Level and destination RF string at E+696 differs case-insensitively from current logical level0x6FC31C. Returns false otherwise. Direct links only, no recursive graph walk. Predicate0x560A00 returns inequality, not equality.
char __cdecl rf_trigger_has_direct_load_to_different_level(int a1)
{
  int *v1; // eax
  int v3; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 724)); ++i )
  {
    v1 = (int *)sub_552200((_DWORD *)(a1 + 724), i);
    v3 = rf_mission_event_find_by_uid(*v1);
    if ( v3 && *(_DWORD *)(v3 + 656) == 22 && rf_string_not_equals_case_insensitive(v3 + 696, (int)unk_6FC31C) )
      return 1;
  }
  return 0;
}

