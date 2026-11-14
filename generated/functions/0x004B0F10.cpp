// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B0F10 rf_multiplayer_send_team_change_to_local_transport23
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Cdecl(networkID lowBYTE,team lowBYTE). If local player nonNULL call4B0F40(localPlayer,id,team); otherwise no action/EAX incidental. No
// runtime/authority gate or identity matching; wrapper destination is local transport, claimed payload ID supplied by caller.
int __cdecl rf_multiplayer_send_team_change_to_local_transport23(char a1, char a2)
{
  int result; // eax

  if ( rf_local_fpgun_player )
    return rf_multiplayer_send_team_change_packet23(rf_local_fpgun_player, a1, a2);
  return result;
}

