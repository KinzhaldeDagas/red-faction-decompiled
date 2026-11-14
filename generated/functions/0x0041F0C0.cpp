// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041F0C0 rf_entity_class_has_secondary_flag20
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): Cdecl entity predicate. NULLfalse;otherwise follows class pointer atentity660 and tests DWORDclass1832 bit0x20,returningbooleanAL. This is SECOND class flag word1832,not primary1828 or runtime entity flags. No class-pointer validation,allocation or mutation;higher gameplay meaning not inferred.
bool __cdecl rf_entity_class_has_secondary_flag20(int a1)
{
  return a1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1832) & 0x20) != 0;
}

