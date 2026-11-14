// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004354A0 rf_entity_class_flags724_has_mask500
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): One cdecl REQUIRED entity pointer, canonicalAL0/1. Dereference class pointer entity+660, test authored class
// DWORD+1828(0x724) mask0x500; ANY selected bit givesAL1 elseAL0. For0x500 either0x100 OR0x400 suffices, not both. No entity/class NULL guard, common runtime-flag/death/player test,
// timer or writes. EAX upper bits incidental; numeric authored mask only, no unproved flag-name mapping.
bool __cdecl rf_entity_class_flags724_has_mask500(int a1)
{
  return (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x500) != 0;
}

