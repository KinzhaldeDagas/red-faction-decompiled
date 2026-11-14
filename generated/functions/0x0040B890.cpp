// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040B890 rf_ai_unholster_pending_flag_set
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Explicit AL1 iff flags DWORD+1328 mask0x100 set; AL0 otherwise. No mutation, deadline read, owner/animation validation
// or full-EAX bool canonicalization.
bool __cdecl rf_ai_unholster_pending_flag_set(int a1)
{
  return (*(_DWORD *)(a1 + 1328) & 0x100) != 0;
}

