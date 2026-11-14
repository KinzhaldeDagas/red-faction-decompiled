// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A03F0 rf_network_flush_player_reliable_queue
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(player), unconditionally dereferences player net DWORD+4608. Requires connection handle net+16 !=-1 and queued length net+2488 signed>0; no runtime/authority/state2 guard.
// Calls rf_reliable_udp_send_queued(handle,net+1976,length), ignores return then resets length+2488=0 even if send fails. Invalid handle or nonpositive length preserves queue. Native
// EAX is player/net-pointer artifact, not send success.
int __cdecl rf_network_flush_player_reliable_queue(int a1)
{
  int result; // eax

  result = a1;
  if ( *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 16) != -1 )
  {
    result = *(_DWORD *)(a1 + 4608);
    if ( *(int *)(result + 2488) > 0 )
    {
      rf_reliable_udp_send_queued(
        *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 16),
        (void *)(*(_DWORD *)(a1 + 4608) + 1976),
        *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 2488));
      *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 2488) = 0;
      return a1;
    }
  }
  return result;
}

