// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050F950 rf_projectile_destroy_runtime
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Stops voice+672 and releases renderer light+676 with force=0 when each handle differs from -1, then resets each to -1. If weapon+664 equals global911C78, scans local players: matching owner entity UID+44, selected weapon+676 equal911C78/911C88, and pending switch+3968=-1 request switch to911C78 with arguments0,1. Unlinks next+652/previous+656 by writing both neighbors, clears own links, returns EAX0. Does not free object or test for another live projectile; list unlink is not idempotent.
int __cdecl rf_projectile_destroy_runtime(_DWORD *a1)
{
  int v2; // [esp+0h] [ebp-Ch]
  int v3; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  if ( a1[168] != -1 )
  {
    rf_gamesound_stop_voice_handle(a1[168]);
    a1[168] = -1;
  }
  if ( a1[169] != -1 )
  {
    rf_renderer_light_release(a1[169], 0);
    a1[169] = -1;
  }
  if ( a1[166] == dword_911C78 )
  {
    for ( i = 0; i < rf_local_player_entry_count; ++i )
    {
      v3 = rf_local_player_entries[i];
      v2 = rf_entity_resolve_handle(*(_DWORD *)(v3 + 20));
      if ( v2
        && *(_DWORD *)(v2 + 44) == a1[12]
        && (*(_DWORD *)(v2 + 676) == unk_911C88 || *(_DWORD *)(v2 + 676) == dword_911C78)
        && *(_DWORD *)(v3 + 3968) == -1 )
      {
        rf_player_request_weapon_switch(v3, dword_911C78, 0, 1);
      }
    }
  }
  *(_DWORD *)(a1[164] + 652) = a1[163];
  *(_DWORD *)(a1[163] + 656) = a1[164];
  a1[163] = 0;
  a1[164] = 0;
  return 0;
}

