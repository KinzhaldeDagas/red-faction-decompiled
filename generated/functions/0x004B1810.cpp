// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1810 rf_tracker_send_sequence_acknowledgment
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Cdecl raw sequence DWORD. Write to unaligned global7B49BB (ACK template7B49B8+3), load LENGTH as unsigned WORD7B49BF, then
// UDP-channel-send(template,length,flags0,endpoint7B2638,channel2). Native WORD, not BYTE. Return transport EAX; no initialization/source/sequence validity guard or timeout state
// writes. Initialized template begins BYTE6,WORD operation1,lengthWORD10; lower transport additionally prefixes channelBYTE2.
int __cdecl rf_tracker_send_sequence_acknowledgment(int a1)
{
  unk_7B49BB = a1;
  return rf_network_send_udp_channel_packet(&unk_7B49B8, unk_7B49BF, 0, (int)&unk_7B2638, 2);
}

