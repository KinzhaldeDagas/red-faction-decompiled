// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00599EC0 rf_network_async_dns_worker
// UNREALRED VERIFIED [network-queues-20261028]: Thread proc ignores parameter and calls gethostbyname on borrowed global hostname0x1BCA314. Lookup failure sets failure byte0x1BCA319=1,returns1. Success,unless suppress byte0x1BCA31A set,stores first h_addr_list IPv4 DWORD raw network order at0x1BCA310 and sets success byte0x1BCA318=1; returns0. Does not validate hostent address family,length,list entry,copy hostname,close thread handle or synchronize globals.
DWORD __stdcall rf_network_async_dns_worker(LPVOID lpThreadParameter)
{
  struct hostent *v2; // [esp+4h] [ebp-4h]

  v2 = gethostbyname(unk_1BCA314);
  if ( v2 )
  {
    if ( !unk_1BCA31A )
    {
      unk_1BCA310 = **(_DWORD **)v2->h_addr_list;
      unk_1BCA318 = 1;
    }
    return 0;
  }
  else
  {
    unk_1BCA319 = 1;
    return 1;
  }
}

