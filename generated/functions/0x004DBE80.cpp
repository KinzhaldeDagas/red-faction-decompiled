// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DBE80 rf_local_players_clear_224_and_reset_weapon_models
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): No arguments. Re-reads signed local entry count each iteration; each entry writes DWORD224=-1, invokes reset-fpgun/remote-charge fallback helper and resets shared cockpit animation latch INSIDE every iteration. No entry NULL guard or vector compaction. Empty/nonpositive count calls no reset helpers; EAX loop/helper residue is not a status/count contract.
int rf_local_players_clear_224_and_reset_weapon_models()
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    *(_DWORD *)(rf_local_player_entries[i] + 224) = -1;
    rf_player_reset_fpgun_and_apply_remote_charge_fallback(rf_local_player_entries[i]);
    rf_vehicle_cockpit_reset_shared_animation_latch();
    result = i + 1;
  }
  return result;
}

