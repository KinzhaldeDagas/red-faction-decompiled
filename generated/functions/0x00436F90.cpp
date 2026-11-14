// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436F90 rf_entity_flags810_has_mask4000
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity pointer), explicit canonical AL0/1, upper EAX not uniformly cleared. NULL returnsAL0; otherwise
// returnsAL1 iff entity DWORD+2064 contains0x4000, elseAL0. No player/type/death/attachment validation, normalization of other flags or writes. Used by player forward-light caller
// but this predicate itself proves only the literal mask.
bool __cdecl rf_entity_flags810_has_mask4000(int a1)
{
  return a1 && (*(_DWORD *)(a1 + 2064) & 0x4000) != 0;
}

