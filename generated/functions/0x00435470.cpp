// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435470 rf_entity_class_flags724_has_mask4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): One cdecl REQUIRED entity pointer, canonicalAL0/1. Dereference class pointer entity+660, test authored class
// DWORD+1828(0x724) mask0x4; ANY selected bit givesAL1 elseAL0. No entity/class NULL guard, common runtime-flag/death/player test, timer or writes. EAX upper bits incidental; numeric
// authored mask only, no unproved flag-name mapping.
bool __cdecl rf_entity_class_flags724_has_mask4(int a1)
{
  return (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 4) != 0;
}

