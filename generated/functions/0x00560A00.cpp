// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560A00 rf_string_not_equals_case_insensitive
// UNREALRED VERIFIED [trigger-airlock-20261022] Case-insensitive comparison used by airlock Load_Level suppression returns nonzero for DIFFERENT strings. Do not invert this into an equality predicate.
// UNREALRED VERIFIED [event-lifecycle-20261028]: Treats first dword as RF-string emptiness indicator. Both zero returns false; exactly one zero returns true. Both nonzero compares character pointers at object+4 using stricmp and returns comparison!=0. This is inequality, not equality; no null object-pointer check.
bool __cdecl rf_string_not_equals_case_insensitive(int a1, int a2)
{
  if ( !*(_DWORD *)a1 && !*(_DWORD *)a2 )
    return 0;
  if ( *(_DWORD *)a1 && *(_DWORD *)a2 )
    return _stricmp(*(const char **)(a1 + 4), *(const char **)(a2 + 4)) != 0;
  return 1;
}

