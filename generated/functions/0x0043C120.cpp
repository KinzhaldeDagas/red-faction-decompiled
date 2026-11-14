// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C120 rf_entity_class_flag2_100
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl entity predicate, canonical AL0/1. NULL returns0; otherwise unchecked class pointer660, test class
// DWORD1832 mask100 and normalize toAL0/1. No other flags/state, mutation or allocation.
bool __cdecl rf_entity_class_flag2_100(int a1)
{
  return a1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1832) & 0x100) != 0;
}

