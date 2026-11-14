// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437F60 rf_entity_descriptor_mode_is_12_15_13_11_or9
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): One cdecl entity pointer; NULL returnsAL0. Otherwise sequential EXACT tests of movement descriptor
// DWORD[entity2136+4] in native order12,15,13,11,9; any match returnsAL1, none returns0. Descriptor pointer is RE-READ for each alternative and not separately NULL-checked. No entity
// speedmode2244, current velocity, class, physics/material, health or clock test and no mutation. Upper EAX incidental; numeric set is the verified contract, not a blanket
// gameplay-state label.
bool __cdecl rf_entity_descriptor_mode_is_12_15_13_11_or9(int a1)
{
  if ( !a1 )
    return 0;
  return *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 12
      || *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 15
      || *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 13
      || *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 11
      || *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 9;
}

