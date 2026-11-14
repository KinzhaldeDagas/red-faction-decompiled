// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A0070 rf_multiplayer_queue_reliable_packet
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Cdecl(player,packet buffer,uint32 size,require active). In runtime mode exactly1 with authority exactly0 replaces supplied player with local player, even if supplied argument was
// nonnull. Otherwise keeps supplied player. Requires player, player DWORD+4608 net data and net DWORD+16 connection handle !=-1. Any nonzero require-active argument additionally
// requires net DWORD+12 exactly2. No own server-only/game-mode guard. Reads packet opcode BYTE0 and signed WORD1 even though size may be0; parsed WORD has no subsequent effect.
// Calls4A6970(net+28,size,1,opcode) before queue operations.
// Queue buffer is net+1976 (7B8h), length DWORD+2488 (9B8h). Native signed32 comparison of wrapping(size+queued length)>512 flushes EXISTING queue through
// rf_reliable_udp_send_queued(handle,buffer,old length), ignores send result and resets length0. Exactly512 does not flush. Then memcpy appends entire incoming size and increments
// queue length, with no own size<=512 check, splitting, truncation, immediate post-append flush or buffer-null validation. Even incoming size>512 is appended whole after prior flush.
// Not a boolean success return; EAX is register artifact.
int __cdecl rf_multiplayer_queue_reliable_packet(int a1, unsigned __int8 *Src, size_t Size, int a4)
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    a1 = rf_local_fpgun_player;
  if ( a1 )
  {
    result = a1;
    if ( *(_DWORD *)(a1 + 4608) )
    {
      if ( *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 16) != -1 )
      {
        if ( !a4 || (result = a1, *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 12) == 2) )
        {
          rf_net_statistics_record_packet((_DWORD *)(*(_DWORD *)(a1 + 4608) + 28), Size, 1, *Src);
          if ( (int)(Size + *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 2488)) > 512 )
          {
            rf_reliable_udp_send_queued(
              *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 16),
              (void *)(*(_DWORD *)(a1 + 4608) + 1976),
              *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 2488));
            *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 2488) = 0;
          }
          memcpy((void *)(*(_DWORD *)(a1 + 4608) + *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 2488) + 1976), Src, Size);
          result = *(_DWORD *)(a1 + 4608);
          *(_DWORD *)(result + 2488) += Size;
        }
      }
    }
  }
  return result;
}

