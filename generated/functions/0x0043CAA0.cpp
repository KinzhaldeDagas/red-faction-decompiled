// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CAA0 rf_entity_movement_descriptor_kind_is2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): One cdecl entity pointer, canonicalAL0/1 only. NULL returns0; otherwise reads movement descriptor DWORD
// entity2136 then descriptor DWORD4==EXACT2. No descriptor NULL guard, model/type/health/authority/timer test or writes. Builds DWORD local0/1 then loads its LOWBYTE intoAL; upperEAX
// incidental. This is current descriptor kind, not descriptor registry index or entity primary AI mode.
bool __cdecl rf_entity_movement_descriptor_kind_is2(int a1)
{
  return a1 && *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 2;
}

