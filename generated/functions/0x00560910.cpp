// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560910 rf_string_object_equals_case_insensitive
// VERIFIED: Compares two executable string objects case-insensitively when both are nonempty; two empty objects compare equal and one empty object does not equal one nonempty object.
// UNREALRED VERIFIED [general-gap-20260830]: Compares two executable string objects case-insensitively; two empty strings compare equal and exactly one empty string compares unequal.
bool __cdecl rf_string_object_equals_case_insensitive(int a1, int a2)
{
  if ( !*(_DWORD *)a1 && !*(_DWORD *)a2 )
    return 1;
  if ( *(_DWORD *)a1 && *(_DWORD *)a2 )
    return _stricmp(*(const char **)(a1 + 4), *(const char **)(a2 + 4)) == 0;
  return 0;
}

