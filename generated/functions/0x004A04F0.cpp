// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A04F0 rf_network_flush_all_player_queues
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// No arguments. In runtime mode EXACTLY1 and authority EXACTLY0, immediately flushes both queues of rf_local_fpgun_player, with no local-pointer null guard. Every other
// mode/authority combination traverses circular player-list87C324 via DWORD0 and skips local player UNCONDITIONALLY, independently of authority==1. This differs from standalone
// reliable/unreliable fanout/flush helpers. Delegates unreliable first then reliable for each admitted player; no own connection/state test. EAX is raw traversal/delegate result.
_DWORD *rf_network_flush_all_player_queues()
{
  _DWORD *result; // eax
  _DWORD *v1; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    return (_DWORD *)rf_network_flush_player_queues(rf_local_fpgun_player);
  result = (_DWORD *)dword_87C324;
  for ( i = (_DWORD *)dword_87C324; i; i = v1 )
  {
    result = i;
    if ( i != (_DWORD *)rf_local_fpgun_player )
      result = (_DWORD *)rf_network_flush_player_queues((int)i);
    if ( *i == dword_87C324 )
    {
      v1 = nullptr;
    }
    else
    {
      result = i;
      v1 = (_DWORD *)*i;
    }
  }
  return result;
}

