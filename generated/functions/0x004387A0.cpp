// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004387A0 rf_entity_custom_mask142C_has_index
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity,32-bit index). NULL or index outside SIGNED inclusive0..31 returnsAL0 without mask read/shift.
// Otherwise forms1<<CL and tests entity DWORD5164(+142C); canonicalAL1 iff that bit set, else0. Reads SECOND mask5164, not neighboring5160. No weapon ownership/model/table lookup or
// other gates/writes. Higher EAX is NOT canonicalized: e.g. successful bit31 can leave80000001, so only AL is Boolean.
bool __cdecl rf_entity_custom_mask142C_has_index(int a1, unsigned int a2)
{
  if ( !a1 )
    return 0;
  if ( a2 < 0x20 )
    return (*(_DWORD *)(a1 + 5164) & (1 << a2)) != 0;
  return 0;
}

