// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059A1C0 rf_reliable_udp_send_opcode6_confirmation
// UNREALRED VERIFIED [network-queues-20261028]: Endpoint argument. Builds10-byte payload: BYTE+0=6,WORD+2=0xFEBD,WORD+4=0; remaining bytes+1,+6..9 are not initialized in body. Stores current elapsed milliseconds in global0x1C0C3F4,then sends0x5995D0(payload,10,flags0,endpoint,channel1). Returns sender result; wire size11 includes channel prefix. Receiver0x59A2C0 recognizes opcode6 in pending state5,sets state4 and ACKs sequence0xFEBD. No retry or local peer allocation in helper.
int __cdecl rf_reliable_udp_send_opcode6_confirmation(int a1)
{
  char Src[2]; // [esp+8h] [ebp-270h] BYREF
  __int16 v3; // [esp+Ah] [ebp-26Eh]
  __int16 v4; // [esp+Ch] [ebp-26Ch]

  Src[0] = 6;
  v3 = -323;
  v4 = 0;
  unk_1C0C3F4 = rf_performance_clock_elapsed_scaled(1000);
  return rf_network_send_udp_channel_packet(Src, 0xAu, 0, a1, 1);
}

