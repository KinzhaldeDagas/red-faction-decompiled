// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004107D0 rf_entity_class_has_contact_geomod_flag200
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl entity predicate;NULLfalse. Otherwise class pointer660 DWORD1828 bit0x200 determines booleanAL. No class-pointer validation,current movement/material check or mutation;used as priority admission for bumper geomod contact branch.
bool __cdecl rf_entity_class_has_contact_geomod_flag200(int a1)
{
  return a1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x200) != 0;
}

