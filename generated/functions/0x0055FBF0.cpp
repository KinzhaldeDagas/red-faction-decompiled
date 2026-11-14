// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055FBF0 rf_string_find_case_insensitive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Thiscall object, C-string needle, reverse byte. NULL/empty needle returns0. Otherwise uses _strnicmp with needle strlen at each index: forward0..extent-1, or backward extent-1..0 when reverse!=0. Returns matching index or-1. Scan bound is stored extent, not current strlen, and match-start eligibility does not subtract needle length. Assumes valid NUL-terminated source/needle; no repair of stale extent or NULL positive-extent buffer.
int __thiscall rf_string_find_case_insensitive(int *this, char *String2, char a3)
{
  unsigned int MaxCount; // [esp+14h] [ebp-8h]
  int v7; // [esp+18h] [ebp-4h]
  int i; // [esp+18h] [ebp-4h]

  if ( !String2 )
    return 0;
  MaxCount = strlen(String2);
  if ( !MaxCount )
    return 0;
  if ( a3 )
  {
    v7 = *this;
    while ( v7-- )
    {
      if ( !_strnicmp((const char *)(v7 + *(this + 1)), String2, MaxCount) )
        return v7;
    }
  }
  else
  {
    for ( i = 0; i < *this; ++i )
    {
      if ( !_strnicmp((const char *)(i + *(this + 1)), String2, MaxCount) )
        return i;
    }
  }
  return -1;
}

