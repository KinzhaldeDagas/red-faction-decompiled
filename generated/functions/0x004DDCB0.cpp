// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DDCB0 rf_player_cycle_candidate_is_usable
// UNREALRED VERIFIED [weapon-cycle] Admits a selector candidate only when slot/category match, the weapon is owned, unrestricted next/previous cycling has positive available ammo, and Grenade reserve is positive.
bool __cdecl rf_player_cycle_candidate_is_usable(int a1, int a2, int a3, int a4)
{
  int v5; // [esp+0h] [ebp-Ch]
  int v6; // [esp+4h] [ebp-8h]
  int v7; // [esp+8h] [ebp-4h]

  if ( a3 != rf_weapon_cycle_slots_category[4 * a2] )
    return 0;
  v7 = rf_player_resolve_entity_inventory(a1);
  if ( !v7 )
    return 0;
  if ( a2 < 0 )
    return 0;
  v6 = rf_weapon_cycle_slots_weapon_index[4 * a2];
  if ( v6 < 0 )
    return 0;
  v5 = rf_player_weapon_available_ammo(a1, v6);
  if ( !sub_403D00(v7, v6) || !v5 && a4 == -1 )
    return 0;
  return v6 != rf_weapon_index_grenade || *(int *)(v7 + 4 * dword_912024[340 * v6] + 12) > 0;
}

