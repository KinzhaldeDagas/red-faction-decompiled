// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00487150 sub_487150
// UNREALRED VERIFIED [ai-authored-startup-20261028] Returns the FIRST exact case-insensitive named waypoint-list match in source order among count 0x700478, records 0x700480 stride0x20C; returns -1 if none. No prefix matching, trimming, or special none handling. Caller 0x4811C0 skips lookup for an empty authored name.
int __cdecl sub_487150(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_700478; ++i )
  {
    if ( rf_string_equals_case_insensitive((int)&dword_700480[131 * i], String2) )
      return i;
  }
  return -1;
}

