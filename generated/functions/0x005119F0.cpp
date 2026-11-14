// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005119F0 sub_5119F0
// UNREALRED VERIFIED [combat-fire-exhaustion-20260930] Bounds-checks the weapon ID and compares it to the Grenade registry ID. Together with exact shoulder_cannon, Rocket Launcher, and HEAP IDs this admits ordinary non-player single-player ammunition exhaustion checking at 0x431FD0, before later mode/flag overrides.
bool __cdecl sub_5119F0(int a1)
{
  return a1 >= 0 && a1 < dword_911C68 && a1 == rf_weapon_index_grenade;
}

