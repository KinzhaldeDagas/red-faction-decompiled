// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560AA0 rf_rf_string_not_equals_cstring_case_insensitive
// UNREALRED VERIFIED [cutscene-ui-20261028]: RF string object arg1 uses empty/length dword+0 and text pointer+4. RF empty and C string null/empty returns false; RF nonempty and C pointer nonnull returns stricmp!=0; otherwise true. No null RF object-pointer guard. Complement of equality for ordinary valid RF strings.
bool __cdecl rf_rf_string_not_equals_cstring_case_insensitive(int a1, char *String2)
{
  if ( !*(_DWORD *)a1 && (!String2 || !*String2) )
    return 0;
  if ( *(_DWORD *)a1 && String2 )
    return _stricmp(*(const char **)(a1 + 4), String2) != 0;
  return 1;
}

