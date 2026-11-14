// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00599F80 rf_network_open_bound_udp_socket
// UNREALRED VERIFIED [network-queues-20261028]: WORD requested port; uses4200 unless port>1023 and !=65535. Stores selected port0x1C0C404,overwrites global socket s with socket(AF_INET=2,SOCK_DGRAM=2,IPPROTO_UDP=17). Socket failure returns sprintf character count of misleading Cannot create TCP socket diagnostic. Binds INADDR_ANY at port; bind failure returns0 WITHOUT closing socket. Success calls0x599C50,attempts broadcast option again,initializes40 peer records0x599F20,sets global0x1C0C3FC=1,returns1. No prior socket close,WSAStartup,connect,listen or TCP socket. Existing enabled flag is not cleared on failure.
int __cdecl rf_network_open_bound_udp_socket(u_short a1)
{
  int result; // eax
  int v2; // [esp+4h] [ebp-12Ch]
  int Error; // [esp+8h] [ebp-128h]
  struct sockaddr name; // [esp+Ch] [ebp-124h] BYREF
  int v5; // [esp+1Ch] [ebp-114h]
  char Buffer[260]; // [esp+20h] [ebp-110h] BYREF
  u_short v7; // [esp+128h] [ebp-8h]
  char optval[4]; // [esp+12Ch] [ebp-4h] BYREF

  v7 = 4200;
  if ( a1 > 0x3FFu && a1 != 0xFFFF )
    v7 = a1;
  s = -1;
  unk_1C0C404 = v7;
  s = socket(2, 2, 17);
  if ( s == -1 )
  {
    Error = WSAGetLastError();
    return sprintf(Buffer, "Cannot create TCP socket (%d)!\n", Error);
  }
  else
  {
    name.sa_family = 2;
    memset(&name.sa_data[2], 0, 12);
    *(_WORD *)name.sa_data = htons(v7);
    if ( bind(s, &name, 16) == -1 )
    {
      v2 = WSAGetLastError();
      sprintf(Buffer, "Couldn't bind TCP socket (%d)! Invalidating TCP\n", v2);
      return 0;
    }
    else
    {
      rf_network_socket_enable_broadcast_nonblocking_receive_buffer(s);
      *(_DWORD *)optval = 1;
      v5 = setsockopt(s, 0xFFFF, 32, optval, 4);
      if ( v5 == -1 )
        WSAGetLastError();
      result = rf_network_initialize_40_peer_records();
      unk_1C0C3FC = 1;
    }
  }
  return result;
}

