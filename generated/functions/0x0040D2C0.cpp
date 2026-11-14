// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D2C0 rf_entity_class_flags724_has_mask800
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl entity pointer; returns AL bool false for null entity, else tests class pointer at entity+660, class DWORD+1828 (0x724) mask0x800. Class pointer itself is not null-checked; no object-type validation or mutation. Used as the fighter-class branch predicate in glare and movement behavior.
bool __cdecl rf_entity_class_flags724_has_mask800(int a1)
{
  return a1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x800) != 0;
}

