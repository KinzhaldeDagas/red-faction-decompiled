// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EC120 rf_player_call_local_fpgun_release_hook
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Cdecl player. Only equality to global local player callsC9F0 with ONE caller-popped DWORD player; hook is native no-op. No separate NULL guard required by no-op; no model release, field/global clearing or useful return. Corrected hook prototype exposes passed argument previously hidden by void().
void __cdecl rf_player_call_local_fpgun_release_hook(int unused_player)
{
  if ( unused_player == rf_local_fpgun_player )
    rf_fpgun_player_release_hook_noop(unused_player);
}

