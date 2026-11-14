// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2740 rf_player_exit_monitor_view
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Assumes player nonNULL. Only when signed own UID DWORD+20>-1: play sound37 with0,0,1; invalidate rendered flag for current view UID+180; set view UID=-1. Negative own UID leaves view target unchanged. Always clear flags+16 bit8 through4E1040, returning player pointer EAX. No requirement that current target resolve or be a monitor before side effects.
int __cdecl rf_player_exit_monitor_view(int a1)
{
  if ( *(int *)(a1 + 20) > -1 )
  {
    rf_gamesound_play_event(37, 0, 0.0, 1.0);
    rf_monitor_invalidate_rendered_flag(*(_DWORD *)(a1 + 180));
    *(_DWORD *)(a1 + 180) = -1;
  }
  return rf_player_clear_flags16_bit8(a1);
}

