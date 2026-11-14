// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A0380 rf_network_flush_all_unreliable_queues
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// No-argument circular player-list87C324 traversal via DWORD0, stopping at root repeat/null. Skips local player only when authority byte EXACTLY1; otherwise includes local. Calls
// flush_player_unreliable_queue for every admitted player. No own runtime/state/net-null admission or list mutation. Delegates can discard queue after failed send. Return EAX is
// traversal/delegate artifact.
int rf_network_flush_all_unreliable_queues()
{
  int result; // eax
  _DWORD *v1; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  result = dword_87C324;
  for ( i = (_DWORD *)dword_87C324; i; i = v1 )
  {
    result = rf_multiplayer_server_authority;
    if ( rf_multiplayer_server_authority != 1 || i != (_DWORD *)rf_local_fpgun_player )
      result = rf_network_flush_player_unreliable_queue((int)i);
    if ( *i == dword_87C324 )
    {
      v1 = nullptr;
    }
    else
    {
      result = (int)i;
      v1 = (_DWORD *)*i;
    }
  }
  return result;
}

