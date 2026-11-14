// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2A00 rf_entity_has_runtime2068_mask800
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): NULL-safe AL predicate: entity exists and DWORD runtime flags+2068 has mask0x800. Does not inspect entity-class flags+1828, player flags or resolve a UID. Sole player-use dispatcher caller; source-level meaning beyond this bit test not assigned.
bool __cdecl rf_entity_has_runtime2068_mask800(int a1)
{
  return a1 && (*(_DWORD *)(a1 + 2068) & 0x800) != 0;
}

