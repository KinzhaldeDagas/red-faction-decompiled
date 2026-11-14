// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040B830 rf_ai_clear_ready_flag
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Single flags DWORD+1328 AND~1 preserving all other bits; EAX retains input block. Does not clear transition flags2/4,
// reset animations/deadlines or alter owner latch.4093E0 separately clears transition mask4.
int __cdecl rf_ai_clear_ready_flag(int a1)
{
  *(_DWORD *)(a1 + 1328) &= ~1u;
  return a1;
}

