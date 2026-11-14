// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040B810 rf_ai_set_ready_flag
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Single flags DWORD+1328 OR mask1 preserving all other bits, returns input block in EAX. Does not touch transition
// masks2/4, owner persistent latch, animation, deadline or target.409260 owns those separate effects.
int __cdecl rf_ai_set_ready_flag(int a1)
{
  *(_DWORD *)(a1 + 1328) |= 1u;
  return a1;
}

