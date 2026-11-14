// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1060 rf_server_broadcast_team_change_packet23
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Cdecl(idBYTE,teamBYTE). Only runtime1 AND authority EXACT1 call4B0F40(NULL,id,team), zero-extend incoming lowBYTEs. No local-pointer prerequisite
// (unlike rate-change broadcast wrapper), ID lookup, team normalization or changed-value check. Preserve delegate/incidental EAX.
int __cdecl rf_server_broadcast_team_change_packet23(char a1, char a2)
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
    return rf_multiplayer_send_team_change_packet23(0, a1, a2);
  return result;
}

