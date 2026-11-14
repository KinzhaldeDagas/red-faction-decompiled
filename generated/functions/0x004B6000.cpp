// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B6000 rf_player_apply_owned_network_weapon_selection
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Cdecl(player,entity,rawWeapon). Ownership query ID=global911C78 if rawWeapon==global911C88, otherwise rawWeapon. Query inventory403D00(entity+672,queryID),
// which accepts only0..63 and nonzero ownership byte; only nonzero AL continues. If selected entityDWORD676 already equals ORIGINAL rawWeapon, no further change. Else call
// player_apply_weapon_selection_by_class(player,ORIGINAL rawWeapon), ignore delegate result, then unconditionally store entity676=rawWeapon. Alias only affects ownership check, not
// selected value/callback. No own pointer/runtime/association check or additional upper bound after alias; EAX original selection/query residue, not uniform bool. Does not broadcast
// directly.
unsigned int __cdecl rf_player_apply_owned_network_weapon_selection(int player, int a2, unsigned int weapon_index)
{
  unsigned int result; // eax
  unsigned int v4; // [esp+0h] [ebp-8h]

  if ( weapon_index == unk_911C88 )
    v4 = dword_911C78;
  else
    v4 = weapon_index;
  result = sub_403D00(a2 + 672, v4);
  if ( (_BYTE)result )
  {
    if ( *(_DWORD *)(a2 + 676) != weapon_index )
    {
      rf_player_apply_weapon_selection_by_class(player, weapon_index);
      *(_DWORD *)(a2 + 676) = weapon_index;
      return weapon_index;
    }
  }
  return result;
}

