// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DCF70 rf_player_weapon_available_ammo
// UNREALRED VERIFIED [weapon-cycle] Returns cycle-selector ammunition as loaded clip plus reserve, counts a live Remote Charge, and treats the Riot Stick as usable when the numeric total is zero.
int __cdecl rf_player_weapon_available_ammo(int a1, int a2)
{
  int v3; // [esp+0h] [ebp-Ch]
  int v4; // [esp+4h] [ebp-8h]
  int v5; // [esp+8h] [ebp-4h]

  if ( !a1 )
    return -1;
  v5 = rf_player_resolve_entity_inventory(a1);
  if ( rf_weapon_has_positive_clip_size(a2) )
    v3 = *(_DWORD *)(v5 + 4 * a2 + 140);
  else
    v3 = 0;
  v4 = v3 + *(_DWORD *)(v5 + 4 * dword_912024[340 * a2] + 12);
  if ( a2 == dword_911C78 || a2 == unk_911C88 )
  {
    v4 += rf_player_has_live_designated_projectile(a1) != 0;
  }
  else if ( a2 == rf_weapon_id_riot_stick && !v4 )
  {
    return 1;
  }
  return v4;
}

