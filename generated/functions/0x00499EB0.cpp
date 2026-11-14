// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499EB0 rf_server_broadcast_entity_spawn_to_remote_peers
// UNREALRED VERIFIED [death-respawn-decode]: Iterates connection-state-2 remote peers, excludes the local server player, and calls the single-peer entity-spawn sender for each.
// Broadcasts packet 44 for a newly created entity to every remote peer in connection state 2, excluding the local server player.
_DWORD *__cdecl rf_server_broadcast_entity_spawn_to_remote_peers(int a1)
{
  _DWORD *result; // eax
  _DWORD *v2; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  result = (_DWORD *)dword_87C324;
  for ( i = (_DWORD *)dword_87C324; i; i = v2 )
  {
    result = i;
    if ( i != (_DWORD *)rf_local_fpgun_player )
    {
      if ( i[1152] )
      {
        result = (_DWORD *)i[1152];
        if ( result[3] == 2 )
          result = (_DWORD *)rf_server_send_entity_spawn_to_peer(a1, (int)i);
      }
    }
    if ( *i == dword_87C324 )
    {
      v2 = nullptr;
    }
    else
    {
      result = i;
      v2 = (_DWORD *)*i;
    }
  }
  return result;
}

