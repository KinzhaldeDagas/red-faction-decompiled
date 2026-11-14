// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D340 rf_entity_class_has_contact_geomod_flag400
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl entity predicate;NULLfalse. Otherwise class pointer660 DWORD1828 bit0x400 determines booleanAL. No class-pointer validation,current movement/material check or mutation;used with material8 and inward speed for contact geomod.
bool __cdecl rf_entity_class_has_contact_geomod_flag400(int a1)
{
  return a1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x400) != 0;
}

