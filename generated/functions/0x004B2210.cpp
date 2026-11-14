// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B2210 rf_multiplayer_broadcast_trigger_activate_packet15
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): Cdecl two raw DWORD arguments,caller pops8. Builds packed11-byte message:BYTEtype15 at0,little-endianWORD payloadlength8 at1,two argument DWORDs at3 and7. Delegates4A01D0(packet,11),which walks player list and queues per-player through49FEE0,skipping local player only when server-authority==1. No own network/player checks or delivery/acknowledgment guarantee;delegate may buffer/flush. Native XOR/JNZ repetition blocks are never taken,not loops that duplicate payload. Security-cookie check after delegate;no native application state changes beyond queue/delegate effects. ReturnEAX incidental delegate result,not successful delivery.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Original descriptor15 at6629FC ->receiver4B2310 identifies previously generic two-DWORD packet: trigger level-ID32 first,activator server handle second.
// Existing11-byte unreliable broadcast ABI unchanged. Receiver only client runtime1 authority0, maps second ID and enables/commits trigger. Native callback source/length unused.
// Binding verified against original PE, no direct caller-name assumption.
int __cdecl rf_multiplayer_broadcast_trigger_activate_packet15(int a1, int a2)
{
  char Src[7]; // [esp+10h] [ebp-208h] BYREF
  int v4; // [esp+17h] [ebp-201h]

  Src[0] = 15;
  *(_DWORD *)&Src[3] = a1;
  v4 = a2;
  *(_WORD *)&Src[1] = 8;
  return rf_multiplayer_broadcast_unreliable_packet(Src, 11);
}

