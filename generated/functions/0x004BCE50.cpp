// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BCE50 rf_entity_matches_local_player_or_related_handle
// UNREALRED VERIFIED [local-multiplayer-lock-20261028] Entry provenance is now traced:0x4DD030 inserts into0x87C5B0 and increments0x87C638 ONLY for a nonzero local-player flag, rejecting a third local entry; every player independently enters all-player list0x87C324. This predicate excludes local-entry resolved entities or candidate.handle==resolvedEntity+0x200. It does not exclude every remote network player. Preserve the related-handle condition without inventing its broader attachment meaning.
// UNREALRED VERIFIED [combat-ammo-roles-pickups-20261111]: Localassociation: nullfalse; scan onlylocalplayerentries count87C638; resolveentry+20. Trueifcandidatepointer==resolvedentity ORresolvedEntity+200==candidateUID+44. This isnot allremoteplayers; preserve relatedhandle case without inventingattachment semantics.
char __cdecl rf_entity_matches_local_player_or_related_handle(int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  if ( !a1 )
    return 0;
  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    v2 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_player_entries[i] + 20));
    if ( v2 && (a1 == v2 || *(_DWORD *)(v2 + 512) == *(_DWORD *)(a1 + 44)) )
      return 1;
  }
  return 0;
}

