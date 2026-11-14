// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437340 rf_entity_class_has_flags724_mask8000
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One cdecl pointer. NULL returns explicitAL0 before dereference. Nonnull loads class pointer DWORD+660, then
// class flags DWORD+1828 (0x724), returns explicitAL1 iff mask0x8000 set, elseAL0. No class-pointer null/type guard, common-object type/dead/inactive/role filtering, field mutation
// or independent gameplay interpretation of the authored flag. Upper EAX bits are incidental; boolean ABI is AL.
bool __cdecl rf_entity_class_has_flags724_mask8000(int a1)
{
  return a1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x8000) != 0;
}

