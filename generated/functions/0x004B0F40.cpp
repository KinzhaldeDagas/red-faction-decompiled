// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B0F40 rf_multiplayer_send_team_change_packet23
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Cdecl(optionalRecipient,networkID lowBYTE,team lowBYTE). Build opcode23,WORD payload2,total5: id at3,raw team at4. No validation/clamp, state mutation
// or own runtime/authority admission. NonNULL recipient ->reliable_queue(recipient,packet,5,requireActive0); NULL ->server_broadcast_packet(packet,5,0). Return delegate EAX. This
// body accepts team values beyond0/1 unchanged.
int __cdecl rf_multiplayer_send_team_change_packet23(int a1, char a2, char a3)
{
  unsigned __int8 Src; // [esp+Ch] [ebp-208h] BYREF
  __int16 v5; // [esp+Dh] [ebp-207h]
  char v6; // [esp+Fh] [ebp-205h]
  char v7; // [esp+10h] [ebp-204h]

  Src = 23;
  v6 = a2;
  v7 = a3;
  v5 = 2;
  if ( a1 )
    return rf_multiplayer_queue_reliable_packet(a1, &Src, 5u, 0);
  else
    return rf_server_broadcast_packet(&Src, 5, 0);
}

