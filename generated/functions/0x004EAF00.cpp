// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EAF00 rf_player_get_target_lock_ready_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Assumes player nonNULL; loads raw BYTE3997 into AL without normalization/global-local check. Existing lock-update routine4EAF20 sets this readiness byte after target-hold timing; accessor has no timer/target validity test or side effects.
char __cdecl rf_player_get_target_lock_ready_byte(int a1)
{
  return *(_BYTE *)(a1 + 3997);
}

