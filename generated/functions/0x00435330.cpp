// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435330 rf_body_action_find_canonical_index
// UNREALRED VERIFIED [mission-play-animation-20261013] Scans45 eight-byte RF string objects at0x683328 using0x560960 exact case-insensitive comparison. Returns canonical body-action index or-1.
int __cdecl rf_body_action_find_canonical_index(char *String1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 45; ++i )
  {
    if ( rf_cstring_equals_rf_string_case_insensitive(String1, 8 * i + 6828840) )
      return i;
  }
  return -1;
}

