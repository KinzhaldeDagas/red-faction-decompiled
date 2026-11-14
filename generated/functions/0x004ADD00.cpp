// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ADD00 rf_multiplayer_broadcast_rate_change_if_local27
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout):
// Cdecl(id BYTE,rate lowWORD). Broadcast wrapper is gated solely by local player pointer NONNULL. If present call4ADBE0(NULL,id,rate); no authority/runtime predicate here. If local
// pointerNULL, no send even if runtime authority1; EAX incidental. Native caller uses this both console server update and incoming packet27 rebroadcast.
int __cdecl rf_multiplayer_broadcast_rate_change_if_local27(unsigned __int8 a1, __int16 a2)
{
  int result; // eax

  if ( rf_local_fpgun_player )
    return rf_multiplayer_send_rate_change_packet27(0, a1, a2);
  return result;
}

