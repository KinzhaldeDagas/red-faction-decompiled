// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474080 rf_item_definition_find_by_given_weapon
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Negative input returns-1; otherwise scans definition count0x6F9124 and returns first index with Gives Weapon dword+64 equal input, else-1. No preference ordering beyond table order.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Find first item ordinal whose BOUND integer GivesWeapon+40 equals requested WID. Negative requested WID returns-1. Binding is performed during472AC0 through native first-name weapon lookup, so same-name later weapon IDs do not match an item bound to the first ID.
int __cdecl rf_item_definition_find_by_given_weapon(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  if ( a1 < 0 )
    return -1;
  for ( i = 0; i < unk_6F9124; ++i )
  {
    if ( unk_6F9170[20 * i] == a1 )
      return i;
  }
  return -1;
}

