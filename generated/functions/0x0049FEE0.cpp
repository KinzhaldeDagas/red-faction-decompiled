// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049FEE0 rf_network_queue_unreliable_player_packet
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Cdecl(player,packet,size signed). NULL packet or size<=0 skips with incidental EAX. In mode1 authority0 overrides player with local player. Requires player/net4608 nonnull and
// reliable-peer slot net16!=-1 EVEN THOUGH queue is UNRELIABLE. Reads opcodeBYTE0 and signed payloadWORD1 (latter unused),calls statistics4A6970(net28,size,1,opcode). No size>=3
// guard before header read.
// If signed(size+queuedDWORD1972)>512,flushes existing bytes from net1460 through network_send_unreliable. Client destination=globals704EF4/F8;otherwise copies first8-byte endpoint
// from player.net. Ignores send result and resets queued count0. Then memcpy appends ENTIRE supplied size atnet1460+count,adds size to count;no independent
// size<=512/remaining-capacity check after flush or integer-overflow repair. Does not force sending newly queued packet,check net connection-state12==2 or validate header length vs
// supplied size. No reliable transmission despite requiring allocated peer slot. Return register incidental,not normalized status.
int __cdecl rf_network_queue_unreliable_player_packet(int a1, char *Src, int Size)
{
  int result; // eax
  u_long *v4; // ecx
  u_long v5; // eax
  u_long v6; // [esp+0h] [ebp-10h] BYREF
  u_long v7; // [esp+4h] [ebp-Ch]
  int v8; // [esp+8h] [ebp-8h]
  int v9; // [esp+Ch] [ebp-4h]

  if ( Src && Size > 0 )
  {
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
          v8 = (unsigned __int8)*Src;
          v9 = *(__int16 *)(Src + 1);
          rf_net_statistics_record_packet((_DWORD *)(*(_DWORD *)(a1 + 4608) + 28), Size, 1, v8);
          if ( Size + *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 1972) > 512 )
          {
            if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
            {
              v4 = *(u_long **)(a1 + 4608);
              v5 = v4[1];
              v6 = *v4;
              v7 = v5;
            }
            else
            {
              v6 = dword_704EF4;
              v7 = unk_704EF8;
            }
            rf_network_send_unreliable(
              (int)&v6,
              (void *)(*(_DWORD *)(a1 + 4608) + 1460),
              *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 1972));
            *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 1972) = 0;
          }
          memcpy((void *)(*(_DWORD *)(a1 + 4608) + *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 1972) + 1460), Src, Size);
          *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 1972) += Size;
          return a1;
        }
      }
    }
  }
  return result;
}

