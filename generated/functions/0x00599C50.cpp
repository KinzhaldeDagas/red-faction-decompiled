// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00599C50 rf_network_socket_enable_broadcast_nonblocking_receive_buffer
// UNREALRED VERIFIED [network-queues-20261028]: Socket argument. Attempts SOL_SOCKET/SO_BROADCAST(32)=1,then FIONBIO0x8004667E=1. Nonblocking error is only formatted into unused local diagnostic; processing continues. Reads SO_RCVBUF4098 then tries32768bytes while signed candidate>=reported size. Failed sets halve candidate unless WSAENOPROTOOPT10042 or WSAEINVAL10022; never intentionally requests below reported size. Reads final size and returns sprintf result for unused Receive buffer set diagnostic,not configuration success. API results except stated branches unchecked; failed getsockopt can leave comparison value uninitialized. Does not close socket.
int __cdecl rf_network_socket_enable_broadcast_nonblocking_receive_buffer(SOCKET s)
{
  int v2; // [esp+0h] [ebp-130h]
  int Error; // [esp+4h] [ebp-12Ch]
  char optval[4]; // [esp+Ch] [ebp-124h] BYREF
  char Buffer[260]; // [esp+10h] [ebp-120h] BYREF
  int v6; // [esp+118h] [ebp-18h]
  int v7; // [esp+11Ch] [ebp-14h]
  char v8[4]; // [esp+120h] [ebp-10h] BYREF
  u_long argp; // [esp+124h] [ebp-Ch] BYREF
  int optlen; // [esp+128h] [ebp-8h] BYREF
  char v11[4]; // [esp+12Ch] [ebp-4h] BYREF

  *(_DWORD *)optval = 1;
  setsockopt(s, 0xFFFF, 32, optval, 4);
  argp = 1;
  v7 = ioctlsocket(s, -2147195266, &argp);
  if ( v7 == -1 )
  {
    Error = WSAGetLastError();
    sprintf(Buffer, "Unable to make socket non-blocking -- %d\n", Error);
  }
  v6 = 0x8000;
  optlen = 4;
  getsockopt(s, 0xFFFF, 4098, v11, &optlen);
  *(_DWORD *)v8 = v6;
  while ( *(int *)v8 >= *(int *)v11 )
  {
    if ( setsockopt(s, 0xFFFF, 4098, v8, 4) != -1 )
      break;
    v2 = WSAGetLastError();
    if ( v2 == 10042 || v2 == 10022 )
      break;
    *(int *)v8 >>= 1;
  }
  getsockopt(s, 0xFFFF, 4098, v11, &optlen);
  return sprintf(Buffer, "Receive buffer set to %d\n", *(_DWORD *)v11);
}

