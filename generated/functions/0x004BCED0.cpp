// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BCED0 rf_object_find_local_player_entry_or_related_owner
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Cdecl input common pointer. Scans local-player entry array in increasing index order, resolving each entry+20 through ENTITY resolver433EE0. First nonnull resolved entity qualifies if pointer-equal input OR its entity association HANDLE512 equals input HANDLE44; returns ARRAY ENTRY pointer, not entity pointer. Otherwise0. No recursive relation search, flag test or mutation. No inputNULL guard: when a resolvable entry is encountered, non-equality path dereferences input+44; empty/unresolvable arrays can return0 without doing so.
int __cdecl rf_object_find_local_player_entry_or_related_owner(int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    v2 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_player_entries[i] + 20));
    if ( v2 && (a1 == v2 || *(_DWORD *)(v2 + 512) == *(_DWORD *)(a1 + 44)) )
      return rf_local_player_entries[i];
  }
  return 0;
}

