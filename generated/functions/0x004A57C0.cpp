// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A57C0 rf_client_apply_enter_limbo_callback21
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Recovered [4A57C0,4A581E), no consumed arguments. Runtime1/authority EXACT0 only. Sets local net state+12=0,OR flags+8 mask20,requests panel34 unforced0. No local/net-null/source
// check. State changes happen before panel admission and persist if request refused. Registry21=enter_limbo.
void __cdecl rf_client_apply_enter_limbo_callback21()
{
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 12) = 0;
    *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) |= 0x20u;
    rf_ui_request_panel_immediate(34, 0);
  }
}

