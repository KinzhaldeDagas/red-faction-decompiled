// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A4A70 rf_console_kick_all_remote_players
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Recovered [4A4A70,4A4AFE), no arguments. Runtime1/authority1 only. Circular traversal SAVES next before calling5590 on each nonlocal player; excludes local, no net-null/state
// filter. After traversal, nonzero console usage flag prints Usage: kick_all; it does NOT suppress kicking. No argument parsing/count guard. Unclassified incoming references do not
// establish command registration; native boundaries/control flow verified.
void __cdecl rf_console_kick_all_remote_players()
{
  _DWORD *v0; // [esp+0h] [ebp-Ch]
  _DWORD *i; // [esp+8h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    for ( i = (_DWORD *)dword_87C324; i; i = v0 )
    {
      if ( *i == dword_87C324 )
        v0 = nullptr;
      else
        v0 = (_DWORD *)*i;
      if ( (_DWORD *)rf_local_fpgun_player != i )
        rf_server_kick_and_remove_player((int)i);
    }
    if ( dword_1809814 )
      rf_console_output_append_text_lines("Usage: kick_all\n", nullptr);
  }
}

