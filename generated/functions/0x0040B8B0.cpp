// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040B8B0 rf_ai_initialize_holstered_pending_state
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. OR mask0x100 and0x200 into flags+1328 in TWO separate stores, then resets deadline+628 to disarmed-1. Does not reset
// deadline+632, set ready mask1, start animation or change entity holster bit+2064/0x800. EAX is deadline-reset helper result.
_DWORD *__cdecl rf_ai_initialize_holstered_pending_state(int a1)
{
  *(_DWORD *)(a1 + 1328) |= 0x100u;
  *(_DWORD *)(a1 + 1328) |= 0x200u;
  return rf_replicator_reset((_DWORD *)(a1 + 628));
}

