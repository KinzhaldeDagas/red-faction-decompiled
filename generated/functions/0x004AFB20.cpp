// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AFB20 rf_multiplayer_send_state_info_done_packet10
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Cdecl recipient. Build opcode10,WORD payload0,total3 bytes; reliable_queue(recipient,packet,3,requireActive0), return delegate EAX. No
// runtime/authority/recipient guard, payload data, timer reset or local net-state write. Server world-state activation uses this as completion marker after history sends.
int __cdecl rf_multiplayer_send_state_info_done_packet10(int a1)
{
  unsigned __int8 Src; // [esp+8h] [ebp-208h] BYREF
  __int16 v3; // [esp+9h] [ebp-207h]

  Src = 10;
  v3 = 0;
  return rf_multiplayer_queue_reliable_packet(a1, &Src, 3u, 0);
}

