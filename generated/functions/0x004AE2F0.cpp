// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AE2F0 rf_splitscreen_reset_respawn_and_shared_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout):
// Noarg. Calls respawn_reset_counts491880, then401250 which unconditionally zeros globalDWORD6663D4. No runtime guard, input arguments, entity creation, level loading or return
// status. Does not itself initialize split match/player viewports; those belong separate4AE300.
void rf_splitscreen_reset_respawn_and_shared_state()
{
  rf_respawn_reset_counts();
  rf_reset_global_dword6663D4();
}

