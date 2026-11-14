// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050FFA0 sub_50FFA0
// UNREALRED VERIFIED [combat-selected-drop-20261111]: Requires signedweaponID in[0,64), nonemptyworldmeshname atrecord+40; returns alreadycachedworldmodel handle+48. Noresource load/fallback occurs here. Missing worldhandle rejects420020 beforeinventorymutation; arbitraryowned/itemmesh substitution is not admitted.
int __cdecl sub_50FFA0(unsigned int a1)
{
  if ( a1 >= 0x40 )
    return 0;
  if ( rf_string_length_from_cstr((const char **)&rf_weapon_records + 340 * a1 + 10) )
    return *((_DWORD *)&rf_weapon_records + 340 * a1 + 12);
  return 0;
}

