// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00510630 rf_weapon_has_alt_fire_flag
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Requires signed0<=weapon_index<global911C68; returns AL boolean of record flags+612 mask1 (authored alt_fire). Invalid index false; no mutation.
bool __cdecl rf_weapon_has_alt_fire_flag(int a1)
{
  return a1 >= 0 && a1 < dword_911C68 && (unk_912264[340 * a1] & 1) != 0;
}

