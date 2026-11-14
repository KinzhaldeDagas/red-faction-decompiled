// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438050 rf_entity_movement_is_index1_or2
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl entity predicate:NULLfalse,otherwise current descriptor2136 DWORD4==1 OR2. Short-circuits after1. Distinct from438010 index1/5 predicate used by grounded traction control. No class-name comparison/descriptor validation;booleanAL,no mutation.
bool __cdecl rf_entity_movement_is_index1_or2(int a1)
{
  if ( !a1 )
    return 0;
  return *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 1 || *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 2;
}

