// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DE390 rf_player_select_owned_weapon_if_present
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): Cdecl player,weapon index. Index EXACTLY-1 returns; otherwise resolves inventory and requires inventory-contains predicate403D00 AL EXACT1, then calls class-based weapon selection(player,index). Missing inventory/non1 predicate does nothing. No own upper-bound, other-negative-index, ammo or model check; no defined return status.
void __cdecl rf_player_select_owned_weapon_if_present(int player, unsigned int weapon_index)
{
  int v2; // [esp+0h] [ebp-4h]

  if ( weapon_index != -1 )
  {
    v2 = rf_player_resolve_entity_inventory(player);
    if ( v2 )
    {
      if ( sub_403D00(v2, weapon_index) )
        rf_player_apply_weapon_selection_by_class(player, weapon_index);
    }
  }
}

