// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00510240 rf_weapon_has_positive_clip_size
// UNREALRED VERIFIED [hud-ammo-general] Returns true only for a valid weapon index whose 1360-byte WeaponInfo record has a clip-size dword greater than zero at offset 0x88.
bool __cdecl rf_weapon_has_positive_clip_size(int a1)
{
  return a1 >= 0 && a1 < dword_911C68 && unk_912088[340 * a1] > 0;
}

