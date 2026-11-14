// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560F10 rf_rf_string_greater_equal_cstring_case_insensitive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Recovered cdecl(RF object left, nullable C string right). Early both-empty rule: leftExtent==0 AND (right==NULL or *right==NUL) returns 1. Else when leftExtent!=0 and right pointer is non-NULL, returns _stricmp(left.buffer,right) >= 0. Otherwise returns objectExtent!=0. Uses stored extent, not strlen; no nonzero-extent buffer guard. Bool result is AL; no mutation.
bool __cdecl rf_rf_string_greater_equal_cstring_case_insensitive(const void *a1, const char *String2)
{
  BOOL v2; // eax

  if ( *(_DWORD *)a1 || String2 && *String2 )
  {
    if ( *(_DWORD *)a1 && String2 )
      LOBYTE(v2) = _stricmp(*((const char **)a1 + 1), String2) >= 0;
    else
      return *(_DWORD *)a1 != 0;
  }
  else
  {
    LOBYTE(v2) = 1;
  }
  return v2;
}

