// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A01D0 rf_multiplayer_broadcast_unreliable_packet
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(packet buffer,signed size). Requires nonnull buffer and signed size>0; otherwise returns with incidental EAX. Iterates circular player list87C324 via player DWORD0 until next
// equals list root or current is null. Skips local player ONLY when authority byte is EXACTLY1; all other authority values admit it. Delegates each eligible player to
// rf_network_queue_unreliable_player_packet(player,buffer,size). No own runtime/game-mode/net-pointer/connection-state guard; client substitution and transport admission remain
// delegated. Does not flush queues. EAX varies with guard, traversal and delegate; not packet count/success.
int __cdecl rf_multiplayer_broadcast_unreliable_packet(char *Src, signed int Size)
{
  int result; // eax
  _DWORD *v3; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  if ( Src && Size > 0 )
  {
    result = dword_87C324;
    for ( i = (_DWORD *)dword_87C324; i; i = v3 )
    {
      result = rf_multiplayer_server_authority;
      if ( rf_multiplayer_server_authority != 1 || i != (_DWORD *)rf_local_fpgun_player )
        result = rf_network_queue_unreliable_player_packet((int)i, Src, Size);
      if ( *i == dword_87C324 )
      {
        v3 = nullptr;
      }
      else
      {
        result = (int)i;
        v3 = (_DWORD *)*i;
      }
    }
  }
  return result;
}

