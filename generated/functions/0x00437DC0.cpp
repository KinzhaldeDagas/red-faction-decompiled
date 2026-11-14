// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437DC0 rf_entity_counter1424_is_nonpositive
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): One cdecl entity pointer; NULL returnsAL0. Otherwise returns canonicalAL1 iff entity DWORD5156(+1424) is
// SIGNED<=0; positive returns0. Zero and all negative values qualify, including INT_MIN. No counter decrement, clock query, reset or other validation/mutation; upper EAX incidental.
bool __cdecl rf_entity_counter1424_is_nonpositive(int a1)
{
  return a1 && *(_DWORD *)(a1 + 5156) <= 0;
}

