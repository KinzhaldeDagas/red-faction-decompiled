// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435A50 rf_entity_class_name_is_hendrix
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): One cdecl entity pointer; NULL returns canonicalAL0. Otherwise compare RFString at gameplay class pointer
// entity660+0 to literal Hendrix through exact case-insensitive55F9B0, ANYnonzero result canonicalized toAL1 else0. This tests CLASS name, not entity RFString24, player identity or
// friendliness; no class-pointer guard, prefix/trim/numeric parsing or writes. UpperEAX incidental.
bool __cdecl rf_entity_class_name_is_hendrix(int a1)
{
  return a1 && rf_string_equals_case_insensitive(*(_DWORD *)(a1 + 660), "Hendrix");
}

