// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040BA60 rf_ai_holstered_flag_is_clear
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Canonical AL1 iff flags+1328 mask0x200 is CLEAR, AL0 when set; this is inverse holstered polarity, not owner entity
// holster-bit predicate. No timer update or other validation.
bool __cdecl rf_ai_holstered_flag_is_clear(int a1)
{
  return (*(_DWORD *)(a1 + 1328) & 0x200) == 0;
}

