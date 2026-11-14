// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00433F60 rf_entity_is_dead
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ordered object-pair type matrix, side-specific INOUT mask writes, native x87 unordered branches and projectile global-plane gate): 
// Cdecl entity pointer, canonical AL bool true for NULL OR entity flags DWORD2064 (0x810) mask1 set; false otherwise. No health52 comparison, common delete flag124 mask2, player
// flag, attachment or class test; no mutation. Used by item/entity pair admission in MP/split/extra-mode paths.
bool __cdecl rf_entity_is_dead(int a1)
{
  return !a1 || (*(_DWORD *)(a1 + 2064) & 1) != 0;
}

