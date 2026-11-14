// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560BB0 rf_rf_string_less_cstring_case_insensitive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Recovered cdecl(RF object left, nullable C string right). Early both-empty rule: leftExtent==0 AND (right==NULL or *right==NUL) returns 0. Else when leftExtent!=0 and right pointer is non-NULL, returns _stricmp(left.buffer,right) < 0. Otherwise returns objectExtent==0. Uses stored extent, not strlen; no nonzero-extent buffer guard. Bool result is AL; no mutation.
bool __cdecl rf_rf_string_less_cstring_case_insensitive(const void *a1, const char *String2)
{
  if ( !*(_DWORD *)a1 && (!String2 || !*String2) )
    return 0;
  if ( *(_DWORD *)a1 && String2 )
    return _stricmp(*((const char **)a1 + 1), String2) < 0;
  return *(_DWORD *)a1 == 0;
}

