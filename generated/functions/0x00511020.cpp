// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511020 rf_weapon_is_riot_stick
// UNREALRED VERIFIED [special-clip-drain-decode]: Tests exact Riot Stick weapon identity.
bool __cdecl rf_weapon_is_riot_stick(int a1)
{
  return a1 == rf_weapon_id_riot_stick;
}

