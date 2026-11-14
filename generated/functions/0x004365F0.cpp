// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004365F0 rf_entity_add_weapon_ammo
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Ammo-add owner: ifAmmoID>=0 floor priornegative LIVEreserve to0, wrapping-add rawquantity, ifreloadinprogress AND receivingWeaponID==selectedPRIMARY add rawquantity to pending13AC, then uppercap LIVEreserve with receivingweaponactiveMax only (no final lowerfloor). Sharedammo with another reloadingweapon does not adjust pending. Positiveclip+loaded<=0+receivingID==selectedPRIMARY calls431790. UnknownAmmoIDnegative skipsoperation; not same as403AB0/431EF0 rawalias.
char __cdecl rf_entity_add_weapon_ammo(int a1, int a2, int a3)
{
  char result; // al
  int v4; // [esp+0h] [ebp-4h]

  result = 80 * a2;
  v4 = dword_912024[340 * a2];
  if ( v4 >= 0 )
  {
    if ( *(int *)(a1 + 4 * v4 + 684) < 0 )
      *(_DWORD *)(a1 + 4 * v4 + 684) = 0;
    *(_DWORD *)(a1 + 4 * v4 + 684) += a3;
    if ( rf_entity_reload_in_progress(a1) && a2 == *(_DWORD *)(a1 + 676) )
      *(_DWORD *)(a1 + 5036) += a3;
    if ( *(_DWORD *)(a1 + 4 * v4 + 684) > unk_912260[340 * a2] )
      *(_DWORD *)(a1 + 4 * v4 + 684) = unk_912260[340 * a2];
    result = rf_weapon_has_positive_clip_size(a2);
    if ( result == 1 )
    {
      result = a1;
      if ( *(int *)(a1 + 4 * a2 + 812) <= 0 && *(_DWORD *)(a1 + 676) == a2 )
        return rf_weapon_reload_request(a1, 0, 0);
    }
  }
  return result;
}

