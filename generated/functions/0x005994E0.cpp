// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005994E0 rf_network_socket_poll_writable
// UNREALRED VERIFIED [network-queues-20261028]: Builds fd_set with global socket s and timeval{0,0}; calls select(-1,NULL,&writefds,NULL,&timeout). Returns-1 on SOCKET_ERROR,otherwise raw select count. No _WSAFDIsSet call,wait,retry or socket validation.
int rf_network_socket_poll_writable()
{
  struct timeval timeout; // [esp+0h] [ebp-114h] BYREF
  int v2; // [esp+8h] [ebp-10Ch]
  fd_set writefds; // [esp+Ch] [ebp-108h] BYREF

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  writefds.fd_count = 0;
  writefds.fd_array[writefds.fd_count++] = s;
  v2 = select(-1, nullptr, &writefds, nullptr, &timeout);
  if ( v2 == -1 )
    return -1;
  else
    return v2;
}

