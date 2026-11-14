// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E1EE0 rf_player_find_usable_preferred_weapon
// UNREALRED VERIFIED [weapon-autoselect] Scans the 32-entry Player+0x1154 preference order for an owned weapon with unlimited ammunition or positive loaded-plus-reserve ammunition. When Player+0xF41 is nonzero it returns the first safe weapon and retains the first damage_self weapon only as fallback.
unsigned int __cdecl rf_player_find_usable_preferred_weapon(int a1)
{
  int v2; // [esp+0h] [ebp-14h]
  int v3; // [esp+4h] [ebp-10h]
  unsigned int v4; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  v2 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !v2 )
    return -1;
  v3 = -1;
  for ( i = 0; i < 32; ++i )
  {
    v4 = *(_DWORD *)(a1 + 4 * i + 4436);
    if ( sub_403D00(v2 + 672, v4)
      && (unk_912260[340 * v4] <= 0 || *(_DWORD *)(v2 + 4 * v4 + 812) + sub_4391D0(v2, v4) > 0) )
    {
      if ( !rf_weapon_can_damage_self(v4) || !*(_BYTE *)(a1 + 3905) )
        return v4;
      if ( v3 == -1 )
        v3 = v4;
    }
  }
  return v3;
}

