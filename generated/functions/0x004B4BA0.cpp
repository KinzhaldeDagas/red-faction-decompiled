// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4BA0 rf_client_apply_ping_callback24
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Recovered [4B4BA0,4B4BC3), no consumed args. Runtime1/authority EXACT0 calls client_send_pong_packet25; otherwise no effect. Empty ping24 identity proven by compiled descriptor
// row24. Ignores dispatch payload/source; sender reply uses shared server endpoint,not supplied source directly.
void __cdecl rf_client_apply_ping_callback24()
{
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    rf_client_send_pong_packet25();
}

