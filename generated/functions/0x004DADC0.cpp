// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DADC0 rf_player_begin_monitor_target
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl player,target handle. Only signed player entity handle20>=0 writes target180 and plays event37; independently ALWAYS ORs player flags DWORD16 with mask8 via helper4E1020 and returns player address. No own target resolution, monitor eligibility, current-view or player NULL check.
int __cdecl rf_player_begin_monitor_target(int a1, int a2)
{
  if ( *(int *)(a1 + 20) > -1 )
  {
    *(_DWORD *)(a1 + 180) = a2;
    rf_gamesound_play_event(37, 0, 0.0, 1.0);
  }
  return rf_player_set_flags16_bit8(a1);
}

