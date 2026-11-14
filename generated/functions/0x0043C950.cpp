// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C950 rf_entity_class_has_angular_decay_flags
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl object pointer predicate; NULL object returns false. Otherwise reads class pointer at object660 WITHOUT checking it, returns whether class DWORD1828 intersects0x401200. Does not inspect object physics flags/current movement descriptor. Used to admit angular view-offset decay; returns boolean AL, no mutation or allocation.
bool __cdecl rf_entity_class_has_angular_decay_flags(int a1)
{
  return a1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x401200) != 0;
}

