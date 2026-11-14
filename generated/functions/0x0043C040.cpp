// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C040 rf_entity_clear_weapon_inventory
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] For non-null entity clear owner+0x810 bit0x800; loop all64 weapon indices calling0x403CB0(owner+0x2A0,index), then selected weapon+0x2A4=-1. No spawned weapon drops or first-person presentation teardown in this helper.
int __cdecl rf_entity_clear_weapon_inventory(int a1)
{
  int result; // eax
  signed int i; // [esp+0h] [ebp-4h]

  if ( a1 )
  {
    *(_DWORD *)(a1 + 2064) &= ~0x800u;
    for ( i = 0; i < 64; ++i )
      rf_ai_remove_weapon_and_clear_shared_ammo(a1 + 672, i);
    *(_DWORD *)(a1 + 676) = -1;
    return a1;
  }
  return result;
}

