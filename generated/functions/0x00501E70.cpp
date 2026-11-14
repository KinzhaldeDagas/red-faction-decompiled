// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501E70 rf_goal_find_level_record_by_name
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] Scan vector0x90B0E0 of pointers; compare each record string at+0x1C with supplied string object using case-insensitive object equality. Return first matching record or0. Goal_Check/Set use raw counter at record+0x2C0. Does not allocate or resolve names through common object identifiers.
int __cdecl rf_goal_find_level_record_by_name(int a1)
{
  _DWORD *v1; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_90B0E0); ++i )
  {
    v1 = (_DWORD *)sub_552200(unk_90B0E0, i);
    if ( rf_string_object_equals_case_insensitive(*v1 + 28, a1) )
      return *(_DWORD *)sub_552200(unk_90B0E0, i);
  }
  return 0;
}

