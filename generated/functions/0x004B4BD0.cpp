// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4BD0 rf_server_send_latency_probe_packet24
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(peer). Requires runtime mode EXACTLY1 and authority EXACTLY1. Builds empty opcode24 packet: BYTE0=24, payload WORD1=0,total3; directly calls rf_network_send_unreliable(player
// net DWORD+4608 as address,buffer,3), without explicitly calling the per-player aggregate queues or statistics recorder. No peer/net-null/connection-handle/state2 guard or own RTT
// timestamp mutation. Guard rejects without send; EAX is delegate/guard/epilogue artifact. Used by statistics timeout/probe state machine.
int __cdecl rf_server_send_latency_probe_packet24(int a1)
{
  int result; // eax
  char v2; // [esp+8h] [ebp-208h] BYREF
  __int16 v3; // [esp+9h] [ebp-207h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v2 = 24;
    v3 = 0;
    return rf_network_send_unreliable(*(_DWORD *)(a1 + 4608), &v2, 3u);
  }
  return result;
}

