// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059A2C0 rf_reliable_udp_service_peers
// UNREALRED VERIFIED [network-queues-20261028]: Polls UDP then drains channel1 queue through0x599480 into global packet0x1C0C428. Header: opcode BYTE+0,sequence WORD+2,payload length WORD+4,timestamp DWORD+6,data+10. No minimum10-byte header or declared-length-versus-datagram validation; queue wrapper ignores supplied610-byte limit. Peer array0x1BCA410 has40 packed1727-byte records,lookup/allocation uses indices1..39. State+1658:0unused,1connected,2timeout,4confirmation received,5pending. Endpoint+1666,receive/send times+1650/+1654,expected receive WORD+1662. Opcode3 handles connection requests,ACKs duplicates but still searches/allocates a new unused slot in same branch. Pending server accepts opcode6 then state4+ACK; pending client accepts ACK data0xFEBD then state1. Connected opcode0 updates ten RTT DWORDs+1674,sorts with FLOAT comparator0x59A250,averages sorted elements5,6
// into+1719,then frees matching send buffer among75 pointers+0 and WORD sequences+300. Opcode4 calls0x59C4F0,opcode5 skips processing; opcode2 remaps to data1. Data1 checks absolute sequence distance<74,additional wrap/order and duplicate checks,allocates600-byte receive buffer among75 pointers+900,stores declared length DWORDs+1200,sequences WORDs+1500,copies unchecked declared length then ACKs. ACK also occurs if receive slots full. IMPORTANT local peer pointer initialized null ONCE before drain loop,not per packet; unmatched later endpoint can reuse preceding peer pointer. Maintenance scans40 records: pending timeout60000ms; connected retransmission delay from RTT+1719 and minimum field+1723,defaults750ms and clamps>=333ms; retries75 pending sends,using opcode1 and current timestamp. WSAEWOULDBLOCK schedules early retry. Connected idle sends opcode5 after10000ms and marks state2
// after40000ms without receive. Clock rollback adjusts selected timestamps. Return normally loop value40,not packet/service success. No locking or comprehensive peer/buffer cleanup on all timeout paths.
int rf_reliable_udp_service_peers()
{
  int result; // eax
  int v1; // edx
  double v2; // st7
  char v3[2]; // [esp+Ch] [ebp-750h] BYREF
  __int16 v4; // [esp+Eh] [ebp-74Eh]
  __int16 v5; // [esp+10h] [ebp-74Ch]
  int v6; // [esp+12h] [ebp-74Ah]
  char Src[2]; // [esp+274h] [ebp-4E8h] BYREF
  __int16 v8; // [esp+276h] [ebp-4E6h]
  __int16 v9; // [esp+278h] [ebp-4E4h]
  int v10; // [esp+27Ah] [ebp-4E2h]
  char v11[606]; // [esp+27Eh] [ebp-4DEh] BYREF
  int v12; // [esp+4DCh] [ebp-280h]
  float v13; // [esp+4E0h] [ebp-27Ch]
  BOOL v14; // [esp+4E4h] [ebp-278h]
  int v15; // [esp+4E8h] [ebp-274h]
  int j; // [esp+4ECh] [ebp-270h]
  _DWORD Base[10]; // [esp+4F0h] [ebp-26Ch] BYREF
  int v18; // [esp+518h] [ebp-244h]
  _DWORD v19[2]; // [esp+51Ch] [ebp-240h] BYREF
  char v20[260]; // [esp+524h] [ebp-238h] BYREF
  int v21; // [esp+628h] [ebp-134h]
  int k; // [esp+62Ch] [ebp-130h]
  int v23; // [esp+630h] [ebp-12Ch]
  char Buffer[256]; // [esp+634h] [ebp-128h] BYREF
  int v25; // [esp+738h] [ebp-24h]
  int v26; // [esp+73Ch] [ebp-20h]
  int v27; // [esp+740h] [ebp-1Ch]
  int i; // [esp+744h] [ebp-18h]
  int v29[2]; // [esp+748h] [ebp-14h] BYREF
  int v30; // [esp+750h] [ebp-Ch]
  int v31; // [esp+754h] [ebp-8h]
  void *v32; // [esp+758h] [ebp-4h]

  v26 = 600;
  v23 = 0;
  rf_network_poll_udp_into_receive_queues();
  v32 = nullptr;
  if ( dword_664810 != -1 && *(_DWORD *)((char *)&unk_1BCAA8A + 1727 * dword_664810) == 5 )
  {
    v25 = rf_performance_clock_elapsed_scaled(1000);
    if ( v25 < dword_1C0C3F4 )
      dword_1C0C3F4 = v25;
    if ( v25 - dword_1C0C3F4 > 750 )
    {
      v21 = rf_reliable_udp_send_opcode6_confirmation((int)&unk_1BCAA92 + 1727 * dword_664810);
      if ( v21 == -1 )
        *(_DWORD *)((char *)&unk_1BCAA86 + 1727 * dword_664810) = rf_performance_clock_elapsed_scaled(1000) - 750;
      else
        *(_DWORD *)((char *)&unk_1BCAA86 + 1727 * dword_664810) = rf_performance_clock_elapsed_scaled(1000);
    }
  }
  v27 = 0;
  do
  {
    result = rf_network_receive_channel_has_sequence_range(1u);
    v27 = result;
    v23 = 0;
    if ( !result )
      break;
    result = rf_network_receive_channel_pop(byte_1C0C428, 610, 0, v29, 1u);
    v23 = result;
    if ( v23 < 0 )
      return sprintf(Buffer, "recvfrom returned an error! -- %d\n", v23);
    if ( !v23 )
      continue;
    if ( byte_1C0C428[0] == 3 )
    {
      for ( i = 1; i < 40; ++i )
      {
        if ( (*(_DWORD *)((char *)&unk_1BCAA8A + 1727 * i) == 1 || *(_DWORD *)((char *)&unk_1BCAA8A + 1727 * i) == 5)
          && !rf_network_compare_endpoints((int)v29, (int)&unk_1BCAA92 + 1727 * i, 1) )
        {
          sprintf(Buffer, "Received duplicate connection request: %d\n", i);
          rf_reliable_udp_send_ack((int)&unk_1BCAA92 + 1727 * i, word_1C0C42A, dword_1C0C42E);
          byte_1C0C428[0] = 7;
        }
      }
      for ( i = 1; i < 40; ++i )
      {
        if ( !*(_DWORD *)((char *)&unk_1BCAA8A + 1727 * i) )
        {
          v1 = 1727 * i;
          *(_DWORD *)((char *)&unk_1BCAA92 + v1) = v29[0];
          *(_DWORD *)((char *)&unk_1BCAA96 + v1) = v29[1];
          unk_1BCAAC2[1727 * i] = 0;
          *(_DWORD *)((char *)&unk_1BCAAC3 + 1727 * i) = 0;
          *(_DWORD *)((char *)&unk_1BCAA8A + 1727 * i) = 5;
          *(_DWORD *)((char *)&unk_1BCAA82 + 1727 * i) = rf_performance_clock_elapsed_scaled(1000);
          *(_DWORD *)((char *)&unk_1BCAACB + 1727 * i) = 750;
          v32 = (char *)&unk_1BCA410 + 1727 * i;
          break;
        }
      }
      if ( i != 40 )
        goto LABEL_94;
      result = 0;
    }
    else
    {
      for ( i = 1; i < 40; ++i )
      {
        if ( !rf_network_compare_endpoints((int)v29, (int)&unk_1BCAA92 + 1727 * i, 1) )
        {
          v32 = (char *)&unk_1BCA410 + 1727 * i;
          v31 = i;
          break;
        }
      }
      if ( v32 )
      {
        *(_DWORD *)((char *)v32 + 1650) = rf_performance_clock_elapsed_scaled(1000);
        if ( *(_DWORD *)((char *)v32 + 1658) != 1 )
        {
          if ( *(_DWORD *)((char *)v32 + 1658) == 5 )
          {
            if ( dword_664810 == -1 )
            {
              if ( byte_1C0C428[0] == 6 )
              {
                *(_DWORD *)((char *)v32 + 1658) = 4;
                result = rf_reliable_udp_send_ack((int)v32 + 1666, word_1C0C42A, dword_1C0C42E);
                continue;
              }
            }
            else if ( !byte_1C0C428[0] )
            {
              result = dword_1C0C432[0];
              v19[1] = dword_1C0C432[0];
              if ( dword_1C0C432[0] == 65213 )
                *(_DWORD *)((char *)v32 + 1658) = 1;
              continue;
            }
          }
          if ( byte_1C0C428[0] != 1 || dword_664810 == -1 )
          {
            sprintf(
              Buffer,
              "Packet from nonconnected socket -- seq: %d status: %d\n",
              word_1C0C42A,
              *(_DWORD *)((char *)v32 + 1658));
            result = rf_performance_clock_elapsed_scaled(1000);
            *(_DWORD *)((char *)v32 + 1650) = result;
            continue;
          }
          *(_DWORD *)((char *)v32 + 1658) = 1;
        }
        *(_DWORD *)((char *)v32 + 1650) = rf_performance_clock_elapsed_scaled(1000);
        result = byte_1C0C428[0];
        if ( byte_1C0C428[0] != 5 )
        {
          if ( byte_1C0C428[0] != 4 )
          {
            if ( !byte_1C0C428[0] )
            {
              ++*(_DWORD *)((char *)v32 + 1715);
              *(_DWORD *)((char *)v32 + 4 * *((unsigned __int8 *)v32 + 1714) + 1674) = *(_DWORD *)((char *)v32 + 1650)
                                                                                     - dword_1C0C42E;
              if ( *(_DWORD *)((char *)v32 + 1715) >= 0xAu )
              {
                for ( j = 0; j < 10; ++j )
                  Base[j] = *(_DWORD *)((char *)v32 + 4 * j + 1674);
                qsort(Base, 0xAu, 4u, (_CoreCrtNonSecureSearchSortCompareFunction)rf_qsort_compare_float32_ascending);
                *(_DWORD *)((char *)v32 + 1719) = (Base[6] + Base[5]) / 2;
              }
              if ( (unsigned __int8)++*((_BYTE *)v32 + 1714) >= 0xAu )
                *((_BYTE *)v32 + 1714) = 0;
              v18 = dword_1C0C432[0];
              for ( i = 0; i < 75; ++i )
              {
                if ( *((_DWORD *)v32 + i) && *((unsigned __int16 *)v32 + i + 150) == v18 )
                {
                  operator delete(*((void **)v32 + i));
                  *((_DWORD *)v32 + i) = 0;
                  *((_WORD *)v32 + i + 150) = 0;
                }
              }
              result = rf_performance_clock_elapsed_scaled(1000);
              *(_DWORD *)((char *)v32 + 1650) = result;
              continue;
            }
            if ( byte_1C0C428[0] == 2 )
              byte_1C0C428[0] = 1;
            result = byte_1C0C428[0];
            if ( byte_1C0C428[0] != 1 )
              continue;
            result = *((unsigned __int16 *)v32 + 831);
            v15 = word_1C0C42A - result;
            if ( v15 < 0 )
              v15 = -v15;
            if ( v15 >= 74 )
              continue;
            v14 = 1;
            if ( *((unsigned __int16 *)v32 + 831) >= 0xFFB5u )
            {
              if ( word_1C0C42A < (int)*((unsigned __int16 *)v32 + 831) )
                v14 = (unsigned __int16)(word_1C0C42A + *((_WORD *)v32 + 831) + 75) <= 0x4Au;
            }
            else
            {
              v14 = *((unsigned __int16 *)v32 + 831) <= (int)word_1C0C42A;
            }
            for ( i = 0; i < 75; ++i )
            {
              if ( *((_DWORD *)v32 + i + 225) && *((unsigned __int16 *)v32 + i + 750) == word_1C0C42A )
                v14 = 0;
            }
            if ( v14 )
            {
              for ( i = 0; i < 75; ++i )
              {
                if ( !*((_DWORD *)v32 + i + 225) )
                {
                  *((_DWORD *)v32 + i + 300) = unk_1C0C42C;
                  *((_DWORD *)v32 + i + 225) = operator new(0x258u);
                  memcpy(*((void **)v32 + i + 225), dword_1C0C432, *((_DWORD *)v32 + i + 300));
                  *((_WORD *)v32 + i + 750) = word_1C0C42A;
                  break;
                }
              }
            }
LABEL_94:
            result = rf_reliable_udp_send_ack((int)v32 + 1666, word_1C0C42A, dword_1C0C42E);
            continue;
          }
          v19[0] = ((_BYTE *)v32 - (_BYTE *)&unk_1BCA410) / 1727;
          result = rf_reliable_udp_close_peer(v19, 0);
        }
      }
      else
      {
        rf_network_format_endpoint_text(v20, 256, (u_long *)v29);
        result = sprintf(Buffer, "Received from %s\n", v20);
      }
    }
  }
  while ( v27 > 0 );
  for ( k = 0; k < 40; ++k )
  {
    v32 = (char *)&unk_1BCA410 + 1727 * k;
    if ( dword_664810 == -1 )
    {
      if ( *(_DWORD *)((char *)v32 + 1658) == 5 )
      {
        v25 = rf_performance_clock_elapsed_scaled(1000);
        if ( v25 < *(_DWORD *)((char *)v32 + 1650) )
          *(_DWORD *)((char *)v32 + 1650) = v25;
        if ( v25 - *(_DWORD *)((char *)v32 + 1650) > 60000 )
        {
          sprintf(Buffer, "Reliable (but in limbo) socket (%d) timed out in nw_WorkReliable().\n", k);
          memset(v32, 0, 0x6BFu);
          *(_DWORD *)((char *)v32 + 1658) = 0;
        }
      }
    }
    else
    {
      v25 = rf_performance_clock_elapsed_scaled(1000);
      if ( v25 < dword_1C0C3F0 )
        dword_1C0C3F0 = v25;
      if ( *(_DWORD *)((char *)v32 + 1658) == 5 && v25 - dword_1C0C3F0 > 60000 )
      {
        *(_DWORD *)((char *)v32 + 1658) = 2;
        sprintf(Buffer, "Reliable socket (%d) timed out in nw_WorkReliable().\n", k);
      }
    }
    if ( *(_DWORD *)((char *)v32 + 1658) == 1 )
    {
      if ( *(_DWORD *)((char *)v32 + 1719) && *(int *)((char *)v32 + 1719) <= 3000 )
      {
        if ( *(_DWORD *)((char *)v32 + 1719) >= *(_DWORD *)((char *)v32 + 1723) )
          v2 = (double)*(int *)((char *)v32 + 1719) * 1.25;
        else
          v2 = (double)*(int *)((char *)v32 + 1723);
        v13 = v2;
      }
      else
      {
        v13 = 750.0;
      }
      if ( v13 < 333.0 )
        v13 = 333.0;
      for ( i = 0; i < 75; ++i )
      {
        if ( *((_DWORD *)v32 + i) )
        {
          v25 = rf_performance_clock_elapsed_scaled(1000);
          if ( v25 < *(_DWORD *)((char *)v32 + 4 * i + 450) )
            *(_DWORD *)((char *)v32 + 4 * i + 450) = v25;
          if ( v13 <= (double)(v25 - *(_DWORD *)((char *)v32 + 4 * i + 450)) )
          {
            v12 = rf_performance_clock_elapsed_scaled(1000);
            Src[0] = 1;
            v8 = *((_WORD *)v32 + i + 150);
            v10 = v12;
            v9 = *((_WORD *)v32 + i + 375);
            memcpy(v11, *((const void **)v32 + i), *((unsigned __int16 *)v32 + i + 375));
            v30 = rf_network_send_udp_channel_packet(
                    Src,
                    *((unsigned __int16 *)v32 + i + 375) + 10,
                    0,
                    (int)v32 + 1666,
                    1);
            if ( v30 == -2 )
            {
              *(_DWORD *)((char *)v32 + 4 * i + 450) = rf_performance_clock_elapsed_scaled(1000) - 3000;
            }
            else
            {
              *(_DWORD *)((char *)v32 + 1654) = rf_performance_clock_elapsed_scaled(1000);
              *(_DWORD *)((char *)v32 + 4 * i + 450) = rf_performance_clock_elapsed_scaled(1000);
            }
          }
        }
      }
      if ( *(_DWORD *)((char *)v32 + 1658) == 1 )
      {
        v25 = rf_performance_clock_elapsed_scaled(1000);
        if ( v25 < *(_DWORD *)((char *)v32 + 1654) )
          *(_DWORD *)((char *)v32 + 1654) = v25;
        if ( v25 - *(_DWORD *)((char *)v32 + 1654) > 10000 )
        {
          v6 = rf_performance_clock_elapsed_scaled(1000);
          v4 = 0;
          v5 = 0;
          v3[0] = 5;
          v30 = rf_network_send_udp_channel_packet(v3, 0xAu, 0, (int)v32 + 1666, 1);
          if ( v30 >= 0 )
            *(_DWORD *)((char *)v32 + 1654) = rf_performance_clock_elapsed_scaled(1000);
        }
        if ( v25 < *(_DWORD *)((char *)v32 + 1650) )
          *(_DWORD *)((char *)v32 + 1650) = v25;
        if ( v25 - *(_DWORD *)((char *)v32 + 1650) > 40000 )
        {
          sprintf(Buffer, "Reliable Socket (%d) timed out in nw_WorkReliable().\n", k);
          *(_DWORD *)((char *)v32 + 1658) = 2;
        }
      }
    }
    result = k + 1;
  }
  return result;
}

