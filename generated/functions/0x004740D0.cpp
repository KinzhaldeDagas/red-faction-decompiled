// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004740D0 rf_item_definition_find_by_ammo_weapon
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Negative input returns-1; otherwise scans definitions and returns first index with Ammo For dword+60 equal input, else-1. No fallback to Gives Weapon.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Find first item ordinal whose BOUND integer AmmoFor+3C equals requested WID, not ammo-pool ID. Negative requested WID returns-1. Preserve row ordinals and parsed field presence when authored empty weapon names exist.
int __cdecl rf_item_definition_find_by_ammo_weapon(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  if ( a1 < 0 )
    return -1;
  for ( i = 0; i < unk_6F9124; ++i )
  {
    if ( unk_6F916C[20 * i] == a1 )
      return i;
  }
  return -1;
}

