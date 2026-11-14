// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BCBF0 rf_object_handle_has_direct_player_flag
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Cdecl runtime handle. Resolves through40CE70 then delegates to direct player-flag predicate4BB430, which safely returns false forNULL and otherwise tests common flags124 mask8. Returns AL bool; no entity type/player-pointer requirement or related-owner lookup. Invalid/unresolved handle therefore false. No mutation.
bool __cdecl rf_object_handle_has_direct_player_flag(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_object_resolve_handle(a1);
  return rf_object_has_player_flag(v2);
}

