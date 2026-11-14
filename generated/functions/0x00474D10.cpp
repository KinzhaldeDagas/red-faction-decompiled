// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474D10 rf_item_apply_default_weapon_or_ammo_pickup
// UNREALRED VERIFIED [item-pickups-20261028]: Resolves entity/item or returns-1. Gives Weapon field definition+64 takes priority: calls rf_inventory_apply_weapon_pickup and returns its status. Else Ammo For+60 calls0x474E90; returns that status only when multiplayer flag is zero, otherwise returns0. Both weapon paths fill caller outputs even when grant helper fails: weapon index, entity dword+812+4*weapon, entity reserve dword+684+4*ammo-type. Nonweapon/nonammo item only shows player message then returns0, leaving outputs untouched. No output-pointer or weapon-index bounds checks here.
// UNREALRED VERIFIED [combat-ammo-roles-pickups-20261111]: Defaultitem dispatcher resolvesentity/item. GivesWeapon resolvedID+64 takespriority andcalls4750C0. Else AmmoFor resolvedWEAPONid+60 calls474E90 (notammoordinal); weapon determines itsAmmoID. Outputreceipt loaded andRAWreserve filledaftercallsevenfailedstatus, withoutnegative-ammo guard. SPreturnsammohelperstatus; MPreturn0forammo branch afterreceipt (serverprechecks separate). Source item rawnames mustresolveexactweaponID, notnormalizedammo family.
int __cdecl rf_item_apply_default_weapon_or_ammo_pickup(int a1, int a2, int a3, _DWORD *a4, _DWORD *a5, _DWORD *a6)
{
  int result; // eax
  int v7; // [esp+0h] [ebp-10h]
  int v8; // [esp+8h] [ebp-8h]
  int v9; // [esp+Ch] [ebp-4h]

  v9 = rf_entity_resolve_handle(a1);
  if ( !v9 )
    return -1;
  v8 = rf_item_resolve_handle(a2);
  if ( !v8 )
    return -1;
  if ( *(_DWORD *)(*(_DWORD *)(v8 + 660) + 64) != -1 )
  {
    result = rf_inventory_apply_weapon_pickup(a1, a2, *(_DWORD *)(*(_DWORD *)(v8 + 660) + 64), a3);
    *a4 = *(_DWORD *)(*(_DWORD *)(v8 + 660) + 64);
    *a5 = *(_DWORD *)(v9 + 4 * *a4 + 812);
    *a6 = *(_DWORD *)(v9 + 4 * dword_912024[340 * *a4] + 684);
    return result;
  }
  if ( *(_DWORD *)(*(_DWORD *)(v8 + 660) + 60) == -1 )
  {
    if ( rf_object_has_player_flag(v9) )
      rf_item_show_local_pickup_message(v9, *(_DWORD *)(v8 + 660), a3, 0);
  }
  else
  {
    v7 = rf_item_apply_ammo_pickup(a1, a2, *(_DWORD *)(*(_DWORD *)(v8 + 660) + 60), a3);
    *a4 = *(_DWORD *)(*(_DWORD *)(v8 + 660) + 60);
    *a5 = *(_DWORD *)(v9 + 4 * *a4 + 812);
    *a6 = *(_DWORD *)(v9 + 4 * dword_912024[340 * *a4] + 684);
    if ( !rf_multiplayer_runtime_mode )
      return v7;
  }
  return 0;
}

