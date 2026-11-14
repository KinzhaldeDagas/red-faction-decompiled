// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059BE80 rf_reliable_udp_send_queued
// UNREALRED VERIFIED [reliable-connections-20261028]: Arguments unsigned peer index,payload,size. Disabled0x1C0C3FC returns0; otherwise services peers,requires index<40 and state1. Finds first of75 null send pointers+0; no slot marks state2 and returns0. Stores size truncated to WORD array+750,allocates600bytes,builds opcode1 header with WORD sequence+2,WORD length+4,timestamp DWORD+6 and data+10; header byte1 is uninitialized. Copies FULL original size into local606-byte payload and600-byte retained heap buffer without bounds check,stores sequence WORD array+300,then sends channel1 with truncated WORD size+10. Retains heap buffer even on errors. WSAEWOULDBLOCK-2 sets slot timestamp DWORD array+450=now-3000 for retry; all other results set now. Increments next-send WORD+1664 regardless send outcome. Returns raw sender result(-1/-2 or wire bytes),0 for precondition/capacity failure. Does
// not fragment or free retained buffer until ACK/close.
int __cdecl rf_reliable_udp_send_queued(unsigned int a1, void *Src, size_t Size)
{
  char v4[2]; // [esp+4h] [ebp-380h] BYREF
  __int16 v5; // [esp+6h] [ebp-37Eh]
  __int16 v6; // [esp+8h] [ebp-37Ch]
  int v7; // [esp+Ah] [ebp-37Ah]
  _BYTE v8[606]; // [esp+Eh] [ebp-376h] BYREF
  int v9; // [esp+26Ch] [ebp-118h]
  int v10; // [esp+270h] [ebp-114h]
  char Buffer[260]; // [esp+274h] [ebp-110h] BYREF
  int i; // [esp+37Ch] [ebp-8h]
  char *v13; // [esp+380h] [ebp-4h]

  if ( !unk_1C0C3FC )
    return 0;
  rf_reliable_udp_service_peers();
  if ( a1 < 0x28 )
  {
    v13 = (char *)&unk_1BCA410 + 1727 * a1;
    if ( *(_DWORD *)(v13 + 1658) == 1 )
    {
      for ( i = 0; ; ++i )
      {
        if ( i >= 75 )
        {
          *(_DWORD *)(v13 + 1658) = 2;
          return 0;
        }
        if ( !*(_DWORD *)&v13[4 * i] )
          break;
      }
      v9 = rf_performance_clock_elapsed_scaled(1000);
      *(_WORD *)&v13[2 * i + 750] = Size;
      *(_DWORD *)&v13[4 * i] = operator new(0x258u);
      v4[0] = 1;
      v7 = v9;
      v6 = Size;
      memcpy(v8, Src, Size);
      v5 = *((_WORD *)v13 + 832);
      *(_WORD *)&v13[2 * i + 300] = *((_WORD *)v13 + 832);
      memcpy(*(void **)&v13[4 * i], Src, Size);
      v10 = rf_network_send_udp_channel_packet(v4, *(unsigned __int16 *)&v13[2 * i + 750] + 10, 0, (int)(v13 + 1666), 1);
      if ( v10 == -2 )
        *(_DWORD *)&v13[4 * i + 450] = rf_performance_clock_elapsed_scaled(1000) - 3000;
      else
        *(_DWORD *)&v13[4 * i + 450] = rf_performance_clock_elapsed_scaled(1000);
      ++*((_WORD *)v13 + 832);
      return v10;
    }
    else
    {
      sprintf(
        Buffer,
        "Can't send packet because of status %d in nw_SendReliable(). socket = %d\n",
        *(_DWORD *)(v13 + 1658),
        a1);
      return 0;
    }
  }
  else
  {
    sprintf(Buffer, "Invalid socket id passed to nw_NewSendReliable() -- %d\n", a1);
    return 0;
  }
}

