// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437FD0 rf_entity_movement_is_index4_or7
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl entity predicate:NULLfalse,otherwise current descriptor2136 DWORD4==4 OR7. Short-circuits after4. No class-name comparison,bitmask or pointer validation of nonNULL entity descriptor. Returns booleanAL,no mutation.
bool __cdecl rf_entity_movement_is_index4_or7(int a1)
{
  if ( !a1 )
    return 0;
  return *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 4 || *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 7;
}

