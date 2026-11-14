// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040B7F0 rf_ai_is_ready_flag_set
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Explicit canonical AL1 iff flags DWORD+1328 mask1 set, elseAL0; full EAX upper bits are not canonicalized. No
// mutation/null guard. Ready set/clear helpers40B810/40B830 operate same mask.
bool __cdecl rf_ai_is_ready_flag_set(int a1)
{
  return (*(_DWORD *)(a1 + 1328) & 1) != 0;
}

