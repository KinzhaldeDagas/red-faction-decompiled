// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004031B0 rf_ai_multiplayer_flag2000000_allows_action
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One cdecl entity pointer. Returns AL1 immediately when BOTH runtime and splitscreen bytes are0, without dereferencing input. Otherwise
// returns AL1 iff entity DWORD+2000 mask0x02000000 is CLEAR, elseAL0. Any nonzero runtime byte selects masked branch, not exact1. No mutations or independent null guard in that
// branch.
bool __cdecl rf_ai_multiplayer_flag2000000_allows_action(int a1)
{
  return !rf_multiplayer_runtime_mode && !rf_splitscreen_runtime_active
      || ((unsigned int)&unk_2000000 & *(_DWORD *)(a1 + 2000)) == 0;
}

