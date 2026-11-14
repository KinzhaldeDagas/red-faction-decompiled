// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511040 rf_weapon_has_flame_flag
// UNREALRED VERIFIED [special-clip-drain-decode]: Tests weapons.tbl Flags2 bit 0x40, whose literal token is flame.
bool __cdecl rf_weapon_has_flame_flag(int a1)
{
  return a1 >= 0 && a1 < dword_911C68 && (*((_DWORD *)&rf_weapon_records + 340 * a1 + 154) & 0x40) != 0;
}

