// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059C0D0 rf_reliable_udp_connect_to_endpoint
// UNREALRED VERIFIED [reliable-connections-20261028]: Arguments peer-index output,server endpoint. Disabled returns without initializing output. Builds global opcode3 request with WORD sequence322 and zero payload length; does not initialize request byte1/timestamp here. Flushes ALL3 receive queues0x59C8F0,zeros610-byte ACK buffer,sends10-byte request on channel1. Send<0 returns. Loop polls UDP,Sleep10ms; ONLY while channel1 queue empty updates clock,retries request after>2000ms and checks rollback. Dequeues other packets until nonempty opcode0 with data DWORD+10==322; does NOT verify endpoint source or minimum header/declared length. Overall timeout test uses clock variable updated only on empty-queue branch,so a continuously nonempty unrelated stream can delay timeout. Then finds free peer1..39,stores provided endpoint,state5,pacing minimum750,time and global client index0x664810,writes
// output. Sends opcode6 confirmation; ONLY result-1 clears/memsets peer (leaves output/global index written). Other outcomes including-2 spin reliable service up to2000ms waiting state1,with no Sleep. No success return,full handshake guarantee or cleanup on every timeout/failure.
void __cdecl rf_reliable_udp_connect_to_endpoint(int *a1, int *a2)
{
  int v2; // ecx
  int v3; // [esp+0h] [ebp-138h]
  int v4; // [esp+8h] [ebp-130h]
  int v5; // [esp+Ch] [ebp-12Ch]
  int v6; // [esp+10h] [ebp-128h] BYREF
  int v7; // [esp+18h] [ebp-120h]
  int v8; // [esp+1Ch] [ebp-11Ch]
  char Buffer[260]; // [esp+20h] [ebp-118h] BYREF
  int v10; // [esp+128h] [ebp-10h]
  int v11; // [esp+12Ch] [ebp-Ch]
  int i; // [esp+130h] [ebp-8h]
  int v13; // [esp+134h] [ebp-4h]

  v13 = 0;
  if ( !unk_1C0C3FC )
    return;
  byte_1C0CCF8[0] = 3;
  unk_1C0CCFA = 322;
  unk_1C0CCFC = 0;
  rf_network_flush_all_receive_queues();
  memset(byte_1C0CA90, 0, 0x262u);
  v7 = 0;
  v8 = rf_network_send_udp_channel_packet(byte_1C0CCF8, 0xAu, 0, (int)a2, 1);
  if ( v8 < 0 )
  {
    sprintf(Buffer, "Unable to send UDP packet in nw_ConnectToServer()! -- %d\n", v8);
    return;
  }
  v13 = rf_performance_clock_elapsed_scaled(1000);
  v5 = v13;
  v10 = v13;
  v11 = 0;
  while ( 1 )
  {
    ++v11;
    rf_network_poll_udp_into_receive_queues();
    Sleep(0xAu);
    if ( !rf_network_receive_channel_has_sequence_range(1u) )
    {
      v10 = rf_performance_clock_elapsed_scaled(1000);
      if ( v10 < v5 )
        v5 = v10;
      if ( v10 - v5 > 2000 )
      {
        v8 = rf_network_send_udp_channel_packet(byte_1C0CCF8, 0xAu, 0, (int)a2, 1);
        if ( v8 <= 0 )
          sprintf(Buffer, "Error sending connection request! -- %d\n", v8);
        else
          v5 = rf_performance_clock_elapsed_scaled(1000);
      }
      if ( v10 < v13 )
        v13 = v10;
      goto LABEL_32;
    }
    v7 = rf_network_receive_channel_pop(byte_1C0CA90, 610, 0, &v6, 1u);
    if ( v7 < 0 )
    {
      sprintf(Buffer, "recvfrom returned an error! -- %d\n", v7);
      return;
    }
    if ( v7 && !byte_1C0CA90[0] && unk_1C0CA9A == 322 )
      break;
LABEL_32:
    if ( v10 - v13 >= 60000 )
      return;
  }
  for ( i = 1; i < 40 && *(_DWORD *)((char *)&unk_1BCAA8A + 1727 * i); ++i )
    ;
  if ( i != 40 )
  {
    v2 = 1727 * i;
    *(_DWORD *)((char *)&unk_1BCAA92 + v2) = *a2;
    *(_DWORD *)((char *)&unk_1BCAA96 + v2) = a2[1];
    *(_DWORD *)((char *)&unk_1BCAA82 + 1727 * i) = rf_performance_clock_elapsed_scaled(1000);
    *(_DWORD *)((char *)&unk_1BCAA8A + 1727 * i) = 5;
    *(_DWORD *)((char *)&unk_1BCAACB + 1727 * i) = 750;
    dword_664810 = i;
    *a1 = i;
    v8 = rf_reliable_udp_send_opcode6_confirmation((int)&unk_1BCAA92 + 1727 * i);
    if ( v8 == -1 )
    {
      *(_DWORD *)((char *)&unk_1BCAA8A + 1727 * i) = 0;
      memset((char *)&unk_1BCA410 + 1727 * i, 0, 0x6BFu);
    }
    else
    {
      dword_1C0C3F0 = rf_performance_clock_elapsed_scaled(1000);
      *(_DWORD *)((char *)&unk_1BCAA86 + 1727 * i) = rf_performance_clock_elapsed_scaled(1000);
      v4 = rf_performance_clock_elapsed_scaled(1000);
      do
      {
        rf_reliable_udp_service_peers();
        v3 = rf_performance_clock_elapsed_scaled(1000);
        if ( v3 < v4 )
          v4 = v3;
      }
      while ( v3 - v4 < 2000 && *(_DWORD *)((char *)&unk_1BCAA8A + 1727 * i) != 1 );
    }
  }
}

