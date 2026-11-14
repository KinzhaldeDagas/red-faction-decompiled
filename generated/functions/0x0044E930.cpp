// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044E930 rf_hud_ammo_icon_resolve
// UNREALRED VERIFIED [hud-ammo-general] Resolves a weapon's ammo-record index and returns that ammo record's HUD bitmap handle, or -1 when no icon is available.
int __cdecl rf_hud_ammo_icon_resolve(int a1)
{
  if ( a1 < 0 )
    return -1;
  if ( dword_912024[340 * a1] >= 0 )
    return unk_911498[5 * dword_912024[340 * a1]];
  return -1;
}

