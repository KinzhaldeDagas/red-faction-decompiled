// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C910 rf_entity_class_flag1000
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl entity predicate. NULL returns0; otherwise unchecked class660 pointer, test DWORD1828 mask1000. Writes
// local DWORD0/1 then loads its low byte intoAL; upper EAX is incidental. No mutation or other state admission.
bool __cdecl rf_entity_class_flag1000(int a1)
{
  return a1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x1000) != 0;
}

