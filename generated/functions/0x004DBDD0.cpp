// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DBDD0 rf_players_destroy_list_and_shutdown_presentation
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): No arguments. Walks circular player list starting global87C324; snapshots next BEFORE calling4DD4D0 destroy/unlink. If next equals CURRENT global head, snapshotsNULL to terminate; destructor can move global head. After all entries, clears global local player and shuts down shared first-person presentation assets. Does not itself duplicate individual record/resource cleanup; no list corruption/cycle guard.
void __cdecl rf_players_destroy_list_and_shutdown_presentation()
{
  _DWORD *v0; // [esp+0h] [ebp-Ch]
  _DWORD *i; // [esp+8h] [ebp-4h]

  for ( i = (_DWORD *)dword_87C324; i; i = v0 )
  {
    if ( *i == dword_87C324 )
      v0 = nullptr;
    else
      v0 = (_DWORD *)*i;
    rf_player_unlink_close_and_destroy_record((int)i);
  }
  rf_local_fpgun_player = 0;
  rf_fpgun_shutdown_presentation_assets();
}

