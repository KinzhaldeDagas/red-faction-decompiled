// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050D7D0 rf_weapon_preload_all_player_weapon_impact_vclips
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile pre/post physics,homing/expiry/render branches,two-argument cone ABI andx87unordered flow,original ECX/stack flow and PE bytes): Loops signed weapon indices0..<global911C68. Only flags+612 mask80h player_wep records call511B30 with one DWORD weapon index, ADD ESP4. Callee is void, preloads impact Vclips; no model load, nonplayer preload or error aggregation. EAX is loop residue, uninitialized for skipped loop.
int rf_weapon_preload_all_player_weapon_impact_vclips()
{
  int result; // eax
  int weapon_index; // [esp+0h] [ebp-4h]

  for ( weapon_index = 0; weapon_index < dword_911C68; ++weapon_index )
  {
    if ( (unk_912264[340 * weapon_index] & 0x80) != 0 )
      rf_weapon_preload_impact_vclips(weapon_index);
    result = weapon_index + 1;
  }
  return result;
}

