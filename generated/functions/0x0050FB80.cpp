// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050FB80 sub_50FB80
// UNREALRED VERIFIED [combat-reaction-literal-names-20261111]: Literal native weapon lookup: scans every record from0 to911C68-1 in registry source order, stride550h, comparing callerCString against each record RFString through560960; first whole case-insensitive match returns its index, otherwise-1. No trim, UI alias, inventory, ammo, visual or default-name substitution. RFL primary glock conversion is a separate caller operation.
int __cdecl sub_50FB80(char *String1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_911C68; ++i )
  {
    if ( rf_cstring_equals_rf_string_case_insensitive(String1, (int)&rf_weapon_records + 1360 * i) )
      return i;
  }
  return -1;
}

