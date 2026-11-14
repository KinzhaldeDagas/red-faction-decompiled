// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A4B00 rf_console_leave_multiplayer_game
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Recovered [4A4B00,4A4B3A), no arguments. Runtime1/authority1 returns immediately. EVERY other combination unconditionally reads local player net+4608 idBYTE+20, then invokes
// client_leave_game(id,reason1). Thus off-runtime or unusual-authority callers may dereference local pointers BEFORE delegate rejects; no own null check. Does not directly close
// socket or force UI.
void __cdecl rf_console_leave_multiplayer_game()
{
  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority != 1 )
    rf_client_leave_game_notify_and_exit(*(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20), 1);
}

