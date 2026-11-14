// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DE300 rf_player_grant_weapon_and_set_reserve_and_clip
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): Cdecl player,weapon index,reserve integer. Resolves entity inventory; missing returns0. Only weapon index EXACTLY-1 skips remaining work and returns incidental inventory address. Otherwise grants weapon with ammo argument-1, ignores grant result; signed min(requestedReserve,weapon DWORD608) overwrites inventory DWORD12+4*weapon DWORD36, then weapon DWORD136 overwrites inventory DWORD140+4*weapon index. Inventory is entity+672, so these are entity reserve684 and clip812 arrays. Negative reserve values retained by signed min; no lower clamp, ammo/weapon index bound or ownership-success check. Returns weapon-index bits on normal grant path, not uniform success.
int *__cdecl rf_player_grant_weapon_and_set_reserve_and_clip(int a1, int a2, int a3)
{
  int *result; // eax
  int *v4; // [esp+0h] [ebp-4h]

  result = (int *)rf_player_resolve_entity_inventory(a1);
  v4 = result;
  if ( result )
  {
    if ( a2 != -1 )
    {
      rf_entity_inventory_grant_weapon(result, a2, -1);
      v4[dword_912024[340 * a2] + 3] = rf_int_min_signed(a3, unk_912260[340 * a2]);
      v4[a2 + 35] = unk_912088[340 * a2];
      return (int *)a2;
    }
  }
  return result;
}

