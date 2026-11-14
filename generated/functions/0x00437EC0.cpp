// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437EC0 rf_entity_descriptor_mode1_and_speedmode1
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): One cdecl entity pointer; NULL returnsAL0. Nonnull entity DEREFERENCES movement descriptor pointer2136 WITHOUT
// its own NULL guard. Returns canonicalAL1 iff descriptor DWORD+4==EXACT1 AND entity DWORD2244(+8C4)==EXACT1. Other nonzero descriptor/mode values reject. No velocity magnitude,
// movement input, timer, model/class/health checks or writes; does not establish physical motion merely from these two numeric states.
bool __cdecl rf_entity_descriptor_mode1_and_speedmode1(int a1)
{
  if ( !a1 )
    return 0;
  return *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 1 && *(_DWORD *)(a1 + 2244) == 1;
}

