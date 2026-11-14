// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A02D0 rf_network_flush_player_unreliable_queue
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(player), no own player/net null guard. Uses DWORD[player+4608] net data and requires connection handle DWORD+16 !=-1 AND queued length DWORD+1972 signed>0. Does not require
// net state2/runtime mode. If authority BYTE EXACTLY1, copies8-byte destination address from net+0/+4; every other value uses shared destination704EF4/704EF8. Calls
// rf_network_send_unreliable(&address,net+1460,length), ignores return and sets net length+1972=0. Invalid handle or nonpositive length leaves queue untouched; no retry/preservation
// on send failure. EAX is pointer/register artifact, not transport result.
int __cdecl rf_network_flush_player_unreliable_queue(int a1)
{
  int result; // eax
  u_long *v2; // eax
  u_long v3; // edx
  u_long v4; // [esp+0h] [ebp-8h] BYREF
  u_long v5; // [esp+4h] [ebp-4h]

  result = a1;
  if ( *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 16) != -1 )
  {
    result = *(_DWORD *)(a1 + 4608);
    if ( *(int *)(result + 1972) > 0 )
    {
      if ( rf_multiplayer_server_authority == 1 )
      {
        v2 = *(u_long **)(a1 + 4608);
        v3 = v2[1];
        v4 = *v2;
        v5 = v3;
      }
      else
      {
        v4 = dword_704EF4;
        v5 = unk_704EF8;
      }
      rf_network_send_unreliable(
        (int)&v4,
        (void *)(*(_DWORD *)(a1 + 4608) + 1460),
        *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 1972));
      result = *(_DWORD *)(a1 + 4608);
      *(_DWORD *)(result + 1972) = 0;
    }
  }
  return result;
}

