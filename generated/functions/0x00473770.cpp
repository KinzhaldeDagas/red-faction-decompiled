// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00473770 rf_item_definition_find_by_name
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Scans signed count0x6F9124, compares caller C string to RF name at0x6F9130+80*i via0x560960, returns first definition index or-1. Case-insensitive; supports null/empty names according to helper semantics. No bounds cap or table mutation here.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Class lookup scans current signed item count and returns FIRST 560960 equality. No trim, normalized map, deduplication or empty-name special case. This ordinal is used by callback registration as well as item spawning.
int __cdecl rf_item_definition_find_by_name(char *String1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < unk_6F9124; ++i )
  {
    if ( rf_cstring_equals_rf_string_case_insensitive(String1, (int)&unk_6F9130 + 80 * i) )
      return i;
  }
  return -1;
}

