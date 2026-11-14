// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059CBA0 rf_cstring_trim_space_tab_lf_copy
// UNREALRED VERIFIED [string-pool-stream-20261028]: Arguments destination,source C string. Trims ONLY bytes space0x20,tab9,linefeed10 from both ends,copies remaining run with strncpy and explicitly appends NUL. Empty/all-trim source writes destination[0]=0; carriage return0x0D remains. No destination capacity or null checks; strncpy overlap unsupported. Return is destination on copy branch but incidental leading-index value on empty branch,not consistent string pointer.
char *__cdecl rf_cstring_trim_space_tab_lf_copy(char *Destination, const char *a2)
{
  char *result; // eax
  int j; // [esp+10h] [ebp-Ch]
  char *i; // [esp+14h] [ebp-8h]
  signed int Count; // [esp+18h] [ebp-4h]

  Count = strlen(a2);
  for ( i = nullptr; (int)i < Count && (a2[(_DWORD)i] == 32 || a2[(_DWORD)i] == 9 || a2[(_DWORD)i] == 10); ++i )
    ;
  result = i;
  if ( i == (char *)Count )
  {
    *Destination = 0;
  }
  else
  {
    for ( j = Count - 1; j >= 0 && (a2[j] == 32 || a2[j] == 9 || a2[j] == 10); --j )
      ;
    result = strncpy(Destination, &a2[(_DWORD)i], j + 1 - (_DWORD)i);
    Destination[j + 1 - (_DWORD)i] = 0;
  }
  return result;
}

