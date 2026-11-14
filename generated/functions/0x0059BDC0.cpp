// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059BDC0 rf_reliable_udp_accept_confirmed_peer
// UNREALRED VERIFIED [reliable-connections-20261028]: Endpoint output argument. Services reliable peers then scans indices1..39 for FIRST state+1658==4. Changes state to1connected,copies8-byte endpoint+1666,formats address to64-byte local then diagnostic global0x18CD828,returns peer index. None returns-1. Does not allocate new record,poll higher-level input or return all pending peers.
int __cdecl rf_reliable_udp_accept_confirmed_peer(u_long *a1)
{
  int v1; // ecx
  char v3[64]; // [esp+0h] [ebp-48h] BYREF
  int i; // [esp+44h] [ebp-4h]

  rf_reliable_udp_service_peers();
  for ( i = 1; i < 40; ++i )
  {
    if ( *(_DWORD *)((char *)&unk_1BCAA8A + 1727 * i) == 4 )
    {
      *(_DWORD *)((char *)&unk_1BCAA8A + 1727 * i) = 1;
      v1 = 1727 * i;
      *a1 = *(_DWORD *)((char *)&unk_1BCAA92 + 1727 * i);
      a1[1] = *(_DWORD *)((char *)&unk_1BCAA96 + v1);
      rf_network_format_endpoint_text(v3, 64, a1);
      sprintf(&unk_18CD828, "Got address from: %s\n", v3);
      return i;
    }
  }
  return -1;
}

