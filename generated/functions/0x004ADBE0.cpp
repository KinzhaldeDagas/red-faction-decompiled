// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ADBE0 rf_multiplayer_send_rate_change_packet27
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout):
// Cdecl(optionalRecipient,id BYTE,rate lowWORD). Build six-byte envelope: opcode27,WORD payload3,networkID BYTE at3,rate raw lowWORD at4. Unsigned16 cursor; no clamp, range check,
// endian conversion beyond native little-endian stores, source ownership or runtime gate. Recipient nonNULL ->reliable_queue(recipient,packet,6,requireActive0); NULL
// ->server_broadcast_packet(packet,6,0). Preserve delegate EAX. Sender accepts rates wider at callers but discards high16;200000->3392. Packet contains claimed playerID, not
// recipient identity necessarily.
int __cdecl rf_multiplayer_send_rate_change_packet27(int a1, unsigned __int8 a2, __int16 a3)
{
  unsigned __int8 Src[4]; // [esp+10h] [ebp-208h] BYREF
  __int16 v5; // [esp+14h] [ebp-204h]

  Src[0] = 27;
  Src[3] = a2;
  v5 = a3;
  *(_WORD *)&Src[1] = 3;
  if ( a1 )
    return rf_multiplayer_queue_reliable_packet(a1, Src, 6u, 0);
  else
    return rf_server_broadcast_packet(Src, 6, 0);
}

