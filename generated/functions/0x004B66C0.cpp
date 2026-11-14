// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B66C0 rf_multiplayer_broadcast_remote_charge_kill_packet36
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Cdecl raw owner-server-ID DWORD,action lowBYTE. Build opcode36,WORD payload5,total8; owner at3..6,action at7. Native temporary action byte at EBP-1 is stack
// scratch, NOT a transmitted byte at packet offset519 despite decompiler oversized-array notation. Broadcast_unreliable_packet(packet,8), return delegate EAX. No
// runtime/authority/source/owner validity gate, normalization or local charge/entity mutation.
int __cdecl rf_multiplayer_broadcast_remote_charge_kill_packet36(int a1, char a2)
{
  char Src[520]; // [esp+10h] [ebp-208h] BYREF

  Src[0] = 36;
  *(_DWORD *)&Src[3] = a1;
  Src[519] = a2;
  Src[7] = a2;
  *(_WORD *)&Src[1] = 5;
  return rf_multiplayer_broadcast_unreliable_packet(Src, 8);
}

