// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511C00 rf_weapon_can_damage_self
// UNREALRED VERIFIED [weapon-autoselect] Returns whether WeaponInfo+0x268 contains Flags2 mask 0x100 (damage_self). Its verified consumers are pickup and automatic preference selection, not radial source-damage admission.
BOOL __cdecl rf_weapon_can_damage_self(int a1)
{
  return (*((_DWORD *)&rf_weapon_records + 340 * a1 + 154) & 0x100) != 0;
}

