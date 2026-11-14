// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004352E0 rf_body_state_find_canonical_index
// UNREALRED VERIFIED [mission-play-animation-20261013] Scans23 eight-byte RF string objects at0x683490 using0x560960 exact case-insensitive comparison. Returns canonical body-state index or-1.
int __cdecl rf_body_state_find_canonical_index(char *String1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 23; ++i )
  {
    if ( rf_cstring_equals_rf_string_case_insensitive(String1, 8 * i + 6829200) )
      return i;
  }
  return -1;
}

