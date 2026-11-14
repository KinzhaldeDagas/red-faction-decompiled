// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BD1F0 rf_entity_has_player_pointer_if_type0
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Cdecl common object pointer. Returns AL bool true iff common type DWORD36==0 AND entity player pointer DWORD5168!=0. Type test short-circuits before large entity offset for other types. Does NOT check common player flag124 mask8 or validate pointed player/view. No objectNULL guard (type field is read first), no mutation. Drives object-view sound dispatch and its positional/nonpositional choice.
bool __cdecl rf_entity_has_player_pointer_if_type0(int a1)
{
  return !*(_DWORD *)(a1 + 36) && *(_DWORD *)(a1 + 5168) != 0;
}

