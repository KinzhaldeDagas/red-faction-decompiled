// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448B40 rf_game_pause_unless_multiplayer_or_already_paused
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Cdecl lockBYTE. Reject when runtime mode EXACT1 OR pauseBYTE EXACT1. PauseBYTE other nonzero values do not block entry. On admission set pauseBYTE=1 and
// lock6EDD3B=input rawBYTE, call sound-backend pause with caller-pushed DWORD words(1,-1),8B cleanup; increment frame-clock accumulator suspend depth; invoke448B30; set local
// player's flags16 bit8 through delegate. No own local-player NULL/authority check or rollback on backend failure. EAX runtime/delegate residue, not coherent Boolean success. Matches
// unpause448BA0 which blocks unforced only lock exact1; other lock values permit unforced resume.
int __cdecl rf_game_pause_unless_multiplayer_or_already_paused(char a1)
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode != 1 && rf_game_paused != 1 )
  {
    rf_game_paused = 1;
    unk_6EDD3B = a1;
    rf_sound_backend_set_paused(1);
    rf_frame_clock_accumulator_suspend_depth_increment();
    rf_game_clock_pause_depth_increment_adapter();
    return rf_player_set_flags16_bit8(rf_local_fpgun_player);
  }
  return result;
}

