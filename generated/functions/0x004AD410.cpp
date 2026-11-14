// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AD410 rf_network_remove_player_flag_nodes
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(player), no mode/authority/player-null guard. Resolves entity from player+20 once. Traverses circular nodes rooted7B2548,next+12,prev+16,owner DWORD0, saving next before
// mutation. For every matching owner unlinks (including singleton/head update),zeros node next/prev,calls operator delete. Native then, ONLY if entity resolved, READS node DWORD+4
// AFTER delete: action0 clears entity DWORD+2068 mask40000 via43C6D0; action1 clears mask20000 via43C660; other actions do nothing. Preserve this actual post-delete read order; no
// pre-delete action cache. Removes all matches even with unresolved entity. Does not remove player record, broadcast or infer named gameplay meaning for these masks.
void __cdecl rf_network_remove_player_flag_nodes(int a1)
{
  int v1; // [esp+0h] [ebp-18h]
  _DWORD *v2; // [esp+4h] [ebp-14h]
  _DWORD *i; // [esp+10h] [ebp-8h]
  int v4; // [esp+14h] [ebp-4h]

  v4 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  for ( i = (_DWORD *)unk_7B2548; i; i = v2 )
  {
    if ( i[3] == unk_7B2548 )
      v2 = nullptr;
    else
      v2 = (_DWORD *)i[3];
    if ( *i == a1 )
    {
      if ( (_DWORD *)unk_7B2548 == i )
      {
        if ( (_DWORD *)i[3] == i )
        {
          i[3] = 0;
          i[4] = 0;
          unk_7B2548 = 0;
          goto LABEL_12;
        }
        unk_7B2548 = i[3];
      }
      *(_DWORD *)(i[4] + 12) = i[3];
      *(_DWORD *)(i[3] + 16) = i[4];
      i[3] = 0;
      i[4] = 0;
LABEL_12:
      operator delete(i);
      if ( v4 )
      {
        v1 = i[1];
        if ( v1 )
        {
          if ( v1 == 1 )
            rf_entity_clear_state814_mask20000(v4);
        }
        else
        {
          rf_entity_clear_state814_mask40000(v4);
        }
      }
      continue;
    }
  }
}

