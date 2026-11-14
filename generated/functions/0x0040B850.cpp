// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040B850 rf_ai_unholster_animation_deadline_active
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Tests deadline+628 armed; false immediately AL0 without elapsed call. Armed ->elapsed nonzero givesAL0, elapsed zero
// givesAL1. No timer reset/arm or flag tests. Boolean result explicitly in AL only.
bool __cdecl rf_ai_unholster_animation_deadline_active(int a1)
{
  return rf_replicator_is_armed((_DWORD *)(a1 + 628)) && !rf_replicator_has_elapsed((int *)(a1 + 628));
}

