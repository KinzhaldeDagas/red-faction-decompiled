// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AED40 rf_splitscreen_stop_announcer_disable_mouse_and_pause
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Noarg. First runs empty counting loop index0..<signed local_player_entry_count; no per-player body or mutations. Stop all11 announcer voice handles, disable
// mouse-centering request, set centering-disabled BYTE1, then game_pause448B40(lock0), return delegate EAX. No split/runtime admission here; pause delegate refuses runtime
// mode1/already exact paused1. No stored-voice reset, player-list cleanup or level teardown.
int rf_splitscreen_stop_announcer_disable_mouse_and_pause()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_local_player_entry_count; ++i )
    ;
  rf_splitscreen_stop_all_announcer_voices();
  rf_mouse_disable_centering_request();
  rf_mouse_set_centering_disabled(1);
  return rf_game_pause_unless_multiplayer_or_already_paused(0);
}

