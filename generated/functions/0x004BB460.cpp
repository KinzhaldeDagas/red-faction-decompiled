// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BB460 rf_object_is_entity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ordered object-pair type matrix, side-specific INOUT mask writes, native x87 unordered branches and projectile global-plane gate): 
// Cdecl common pointer; canonical AL bool true only when nonnull and type DWORD36==0. NULL false without dereference. No health/flag/class/player-pointer validation or mutation; used
// after common friendliness reads in projectile owner gate.
bool __cdecl rf_object_is_entity(int a1)
{
  return a1 && *(_DWORD *)(a1 + 36) == 0;
}

