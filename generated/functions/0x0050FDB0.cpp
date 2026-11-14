// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050FDB0 rf_weapon_selected_mode_is_continuous_exact_selector
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Requires signed 0<=weapon_index<global911C68, otherwise AL0. Flags+612: continuous_fire bit2 with selector LOW BYTE=0 or alt_continuous_fire bit4 with low byte EXACTLY1 yields AL1. Other low-byte values always false, even when both flags set. Reads configuration, not current firing state.
bool __cdecl rf_weapon_selected_mode_is_continuous_exact_selector(int a1, char a2)
{
  if ( a1 < 0 || a1 >= dword_911C68 )
    return 0;
  if ( (*((_DWORD *)&rf_weapon_records + 340 * a1 + 153) & 2) != 0 && !a2 )
    return 1;
  return (*((_DWORD *)&rf_weapon_records + 340 * a1 + 153) & 4) != 0 && a2 == 1;
}

