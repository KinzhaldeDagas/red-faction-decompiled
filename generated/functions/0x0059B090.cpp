// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059B090 rf_network_poll_udp_into_receive_queues
// UNREALRED VERIFIED [system-progress-20261028]: First advances statistics0x599240. Repeatedly polls global socket s with select zero timeout, exits on SOCKET_ERROR or socket not set. recvfrom buffer max680bytes; converts source port ntohs and IP ntohl, exits on receive error. Packets<3bytes or first byte>=3 are discarded. For channel0..2,adds received bytes and fixed30 overhead to stats(category channel==1),then queues payload excluding first channel byte via0x599740 at0x1BDB3D0+66828*channel. Endpoint is8-byte local containing host-order IP and port. Queue-full drop still counts stats. No blocking wait,packet callback execution,length framing validation or socket lifetime guard. Return is incidental select/FDIsSet/IP result,not packet count.
int rf_network_poll_udp_into_receive_queues()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-3E0h]
  struct timeval timeout; // [esp+4h] [ebp-3DCh] BYREF
  int fromlen; // [esp+Ch] [ebp-3D4h] BYREF
  struct sockaddr from; // [esp+10h] [ebp-3D0h] BYREF
  fd_set readfds; // [esp+20h] [ebp-3C0h] BYREF
  char buf; // [esp+128h] [ebp-2B8h] BYREF
  _BYTE Src[679]; // [esp+129h] [ebp-2B7h] BYREF
  int v8; // [esp+3D4h] [ebp-Ch]
  int v9; // [esp+3D8h] [ebp-8h] BYREF
  u_short v10; // [esp+3DCh] [ebp-4h]

  rf_network_statistics_advance_second_bucket();
  while ( 1 )
  {
    readfds.fd_count = 0;
    fromlen = 0;
    readfds.fd_array[readfds.fd_count++] = s;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    result = select(0, &readfds, nullptr, nullptr, &timeout);
    if ( result == -1 )
      break;
    result = _WSAFDIsSet(s, &readfds);
    if ( !result )
      break;
    fromlen = 16;
    v8 = recvfrom(s, &buf, 680, 0, &from, &fromlen);
    v10 = ntohs(*(u_short *)from.sa_data);
    result = ntohl(*(u_long *)&from.sa_data[2]);
    v9 = result;
    if ( v8 == -1 )
      break;
    if ( v8 >= 3 )
    {
      v1 = (unsigned __int8)buf;
      if ( (unsigned __int8)buf < 3u )
      {
        rf_network_statistics_add_bucket_value(v8, 0, 0, buf == 1);
        rf_network_statistics_add_bucket_value(30, 1, 0, v1 == 1);
        rf_network_receive_queue_append(&unk_1BDB3D0[16707 * v1], Src, v8 - 1, &v9);
      }
    }
  }
  return result;
}

