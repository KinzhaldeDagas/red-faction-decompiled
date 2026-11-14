// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437F00 rf_entity_uses_fall_or_airborne_vehicle_motion
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl entity predicate. NULL returnsfalse. True if current descriptor2136 DWORD4 equals3 OR8,or use-vehicle classification helper succeeds AND current material4992 equals integer-1. Otherwise false. First two descriptor tests short-circuit vehicle query;uses current descriptor,not class defaults. No own descriptor pointer validation or grounded geometry query;no mutation.
bool __cdecl rf_entity_uses_fall_or_airborne_vehicle_motion(_DWORD *a1)
{
  if ( !a1 )
    return 0;
  return *(_DWORD *)(a1[534] + 4) == 3
      || *(_DWORD *)(a1[534] + 4) == 8
      || rf_object_is_use_vehicle(a1) && a1[1248] == -1;
}

