// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438FD0 rf_entity_runtime_flags810_has_mask2000
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): One cdecl entity pointer, canonicalAL0/1. NULL0; otherwise returns1 iff runtime DWORD entity2064(0x810)
// mask0x2000 set. No class authored-flag query, player/weapon/health/authority test, timer or writes. UpperEAX incidental.
bool __cdecl rf_entity_runtime_flags810_has_mask2000(int a1)
{
  return a1 && (*(_DWORD *)(a1 + 2064) & 0x2000) != 0;
}

