// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448BA0 rf_game_unpause_unless_locked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout): Cdecl
// forceBYTE. If paused byte zero return without mutation; if lock byte6EDD3B EXACT1 and forceBYTE0 likewise leave paused. Other lock byte values admit without force. On admission
// clear paused and lock bytes FIRST; call sound-backend resume with caller-pushed DWORD words(0,-1),8-byte cleanup; decrement frame-clock accumulator suspend depth; invoke448B20;
// query local player's monitor view, and if false clear player flags16 bit8 through delegate. No own local-player NULL/runtime guard; helper contracts apply. Does not validate
// suspend depth before decrement or roll back pause bytes after backend/callback failure. Nominal char return AL residue/predicate/delegate rather than uniform unpause success. Split
// input reset4AE510 calls force0, so exact lock1 can prevent resume.
char __cdecl rf_game_unpause_unless_locked(char a1)
{
  char result; // al

  result = rf_game_paused;
  if ( rf_game_paused && (unk_6EDD3B != 1 || a1) )
  {
    rf_game_paused = 0;
    unk_6EDD3B = 0;
    rf_sound_backend_set_paused(0);
    rf_frame_clock_accumulator_suspend_depth_decrement();
    rf_game_clock_pause_depth_decrement_adapter();
    result = rf_player_view_target_is_monitor(rf_local_fpgun_player);
    if ( !result )
      return rf_player_clear_flags16_bit8(rf_local_fpgun_player);
  }
  return result;
}

