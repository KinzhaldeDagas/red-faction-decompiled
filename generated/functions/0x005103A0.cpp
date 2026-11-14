// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005103A0 rf_weapon_selected_mode_has_high_parameter_flag
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Requires0<=weapon_index<global911C68. Returns AL1 iff selector LOW BYTE EXACTLY1 and flags+612 mask10000000, OR byte EXACTLY0 and mask08000000. Other selector bytes false. These high derived flags are not entries in the23-name authored flag table; source-level parameter meaning not assigned here.
bool __cdecl rf_weapon_selected_mode_has_high_parameter_flag(int a1, char a2)
{
  if ( a1 < 0 || a1 >= dword_911C68 )
    return 0;
  if ( (*((_DWORD *)&rf_weapon_records + 340 * a1 + 153) & 0x10000000) != 0 && a2 == 1 )
    return 1;
  return (*((_DWORD *)&rf_weapon_records + 340 * a1 + 153) & 0x8000000) != 0 && !a2;
}

