// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560B50 rf_cstring_less_rf_string_case_insensitive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Recovered cdecl(C string left, RF object right). Early both-empty rule: (left==NULL or *left==NUL) AND rightExtent==0 returns 0. Else when left pointer is non-NULL and rightExtent!=0, returns _stricmp(left,right.buffer) < 0. Otherwise returns objectExtent>0. The CRT branch tests pointer presence, not nonempty first byte. RF object itself must be valid; no buffer guard for nonzero extent. Bool result is AL; no mutation.
bool __cdecl rf_cstring_less_rf_string_case_insensitive(const char *String1, const void *a2)
{
  BOOL v2; // eax

  if ( String1 && *String1 || *(_DWORD *)a2 )
  {
    if ( String1 && *(_DWORD *)a2 )
      LOBYTE(v2) = _stricmp(String1, *((const char **)a2 + 1)) < 0;
    else
      return *(_DWORD *)a2 > 0;
  }
  else
  {
    LOBYTE(v2) = 0;
  }
  return v2;
}

