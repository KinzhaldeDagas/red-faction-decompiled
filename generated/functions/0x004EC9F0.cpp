// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EC9F0 rf_fpgun_player_release_hook_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Native body PUSH EBP/MOV EBP,ESP/POP EBP/RET only. Both callers4DF060 and4EC120 push one player DWORD and pop4; restored ignored-argument cdecl void signature. Reads no argument or globals, does not free/reset any fpgun resource, and does not initialize EAX. Existing function classification retained.
void __cdecl rf_fpgun_player_release_hook_noop(int unused_player)
{
  ;
}

