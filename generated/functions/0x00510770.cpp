// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00510770 rf_weapon_has_scanner_flag
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Requires signed0<=weapon_index<global911C68; returns AL boolean of record second flags DWORD+616 mask80h (authored has_scanner). Invalid index false; no mutation.
bool __cdecl rf_weapon_has_scanner_flag(int a1)
{
  return a1 >= 0 && a1 < dword_911C68 && (*((_DWORD *)&rf_weapon_records + 340 * a1 + 154) & 0x80) != 0;
}

