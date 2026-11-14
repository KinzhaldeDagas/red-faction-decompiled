// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DBFF0 rf_local_players_update_runtime
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): No arguments. Iterates signed global local-player count, re-reading it each time, and calls per-player runtime updater4DC030 for each stored entry. No entry NULL/slot-cap checks, return aggregation or fixed snapshot of count. EAX loop/helper residue is not uniform status.
int rf_local_players_update_runtime()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    rf_player_update_runtime_actions_and_projectiles(rf_local_player_entries[i]);
    result = i + 1;
  }
  return result;
}

