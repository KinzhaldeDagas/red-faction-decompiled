// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560960 rf_cstring_equals_rf_string_case_insensitive
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Compares optional C string arg1 with RF string arg2 (length/empty word+0, character pointer+4). If arg1 null or first byte0 AND RF empty word0, returns true. If both C pointer and RF length nonzero, returns stricmp==0; otherwise false. No null RF object-pointer guard.
// UNREALRED VERIFIED [combat-reaction-literal-names-20261111]: Weapon-name lookup50FB80 uses this whole CString/RFString comparison. The two original buffers go straight to _stricmp at560998; leading/trailing spaces and LF payload remain significant. Null/empty CString matches only RF extent0. This helper performs no whitespace normalization.
bool __cdecl rf_cstring_equals_rf_string_case_insensitive(char *String1, int a2)
{
  if ( (!String1 || !*String1) && !*(_DWORD *)a2 )
    return 1;
  if ( String1 && *(_DWORD *)a2 )
    return _stricmp(String1, *(const char **)(a2 + 4)) == 0;
  return 0;
}

