// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005995D0 rf_network_send_udp_channel_packet
// UNREALRED VERIFIED [network-queues-20261028]: Arguments payload,size,sendto flags,endpoint pointer,channel. Prefixes low8 channel byte to payload in fixed836-byte stack buffer; no size/channel bounds check. Builds AF_INET sockaddr with endpoint host-order DWORD IP and WORD port at+4 converted htonl/htons,sendto(global s,buffer,size+1,flags,...,16). WSAEWOULDBLOCK10035 returns-2,other socket error-1. Any nonnegative send result counts requested size+1 and fixed30 overhead in statistics with category channel==1,then returns raw send result. No partial-send handling or queueing. Sockaddr padding is not explicitly initialized.
int __cdecl rf_network_send_udp_channel_packet(void *Src, size_t Size, int flags, int a4, int a5)
{
  int v6; // [esp+4h] [ebp-35Ch]
  char buf; // [esp+8h] [ebp-358h] BYREF
  _BYTE v8[835]; // [esp+9h] [ebp-357h] BYREF
  struct sockaddr to; // [esp+34Ch] [ebp-14h] BYREF

  buf = a5;
  memcpy(v8, Src, Size);
  to.sa_family = 2;
  *(_WORD *)to.sa_data = htons(*(_WORD *)(a4 + 4));
  *(_DWORD *)&to.sa_data[2] = htonl(*(_DWORD *)a4);
  v6 = sendto(s, &buf, Size + 1, flags, &to, 16);
  if ( v6 == -1 )
  {
    if ( WSAGetLastError() == 10035 )
      return -2;
    else
      return -1;
  }
  else
  {
    rf_network_statistics_add_bucket_value(Size + 1, 0, 1, a5 == 1);
    rf_network_statistics_add_bucket_value(30, 1, 1, a5 == 1);
    return v6;
  }
}

