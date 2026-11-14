// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ADBB0 rf_multiplayer_send_rate_change_to_local_transport27
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout):
// Cdecl(networkID BYTE,rate lowWORD). If local player nonNULL call4ADBE0(localPlayer,id,rate), zero-extending stack args to lowBYTE/WORD. Otherwise do nothing with incidental EAX. No
// runtime/server admission or own net validation; wrapper name describes destination transport, not a sender ownership check.
int __cdecl rf_multiplayer_send_rate_change_to_local_transport27(unsigned __int8 a1, __int16 a2)
{
  int result; // eax

  if ( rf_local_fpgun_player )
    return rf_multiplayer_send_rate_change_packet27(rf_local_fpgun_player, a1, a2);
  return result;
}

