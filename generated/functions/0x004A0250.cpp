// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A0250 rf_server_broadcast_packet
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(packet buffer,signed size,require-active). Requires nonnull buffer and signed size>0. Circular player-list87C324 traversal follows DWORD0 and stops when next equals root;
// null root yields no sends. Skips local player ONLY for authority byte EXACTLY1; no own runtime or server-only guard. Calls
// rf_multiplayer_queue_reliable_packet(player,buffer,size,require-active), preserving the raw third argument (any nonzero delegates state2 requirement). Client-mode queue helper can
// substitute local player for every supplied player, so fanout does not itself prevent repeated local queueing under client-mode use. No direct flush, connection-state test or
// packet-length validation here. EAX is incidental, not success/count; preserves existing transport name and prior comments.
int __cdecl rf_server_broadcast_packet(unsigned __int8 *Src, int Size, int a3)
{
  int result; // eax
  _DWORD *v4; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  if ( Src && Size > 0 )
  {
    result = dword_87C324;
    for ( i = (_DWORD *)dword_87C324; i; i = v4 )
    {
      result = rf_multiplayer_server_authority;
      if ( rf_multiplayer_server_authority != 1 || i != (_DWORD *)rf_local_fpgun_player )
        result = rf_multiplayer_queue_reliable_packet((int)i, Src, Size, a3);
      if ( *i == dword_87C324 )
      {
        v4 = nullptr;
      }
      else
      {
        result = (int)i;
        v4 = (_DWORD *)*i;
      }
    }
  }
  return result;
}

