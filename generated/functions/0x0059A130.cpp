// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059A130 rf_reliable_udp_send_ack
// UNREALRED VERIFIED [network-queues-20261028]: Arguments endpoint,acknowledged sequence,echo timestamp. Builds14-byte payload: opcode BYTE+0=0,length WORD+4=4,timestamp DWORD+6=arg3,acknowledged sequence DWORD+10=arg2. WORD+4 is payload length,not opcode. Bytes+1..3 are NOT initialized before send. Calls0x5995D0(payload,14,flags0,endpoint,channel1),wire size15. Receiver0x59A2C0 uses echoed timestamp for RTT and data DWORD for matching queued send sequence. Returns sender result; no local slot update.
int __cdecl rf_reliable_udp_send_ack(int a1, int a2, int a3)
{
  _BYTE Src[4]; // [esp+Ch] [ebp-270h] BYREF
  __int16 v5; // [esp+10h] [ebp-26Ch]
  int v6; // [esp+12h] [ebp-26Ah]
  int v7; // [esp+16h] [ebp-266h]

  Src[0] = 0;
  v5 = 4;
  v6 = a3;
  v7 = a2;
  return rf_network_send_udp_channel_packet(Src, 0xEu, 0, a1, 1);
}

