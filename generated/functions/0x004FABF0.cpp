// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FABF0 rf_goal_find_shared_record_by_name
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] Scan count at0x90B050 over16-byte records starting0x90B0F0. Compare each record string with supplied C string using rf_string_equals_case_insensitive; first match returns record base, missing returns0. Goal_Check/Set read/write count at returned record+0xC. This lookup alone does not establish save/restore ownership of the shared table.
char *__cdecl rf_goal_find_shared_record_by_name(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_90B050; ++i )
  {
    if ( rf_string_equals_case_insensitive((int)&byte_90B0F0[16 * i], String2) )
      return &byte_90B0F0[16 * i];
  }
  return nullptr;
}

