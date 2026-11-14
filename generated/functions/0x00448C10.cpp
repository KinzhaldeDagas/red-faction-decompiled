// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448C10 rf_game_pause_gate_query
// UNREALRED VERIFIED [hud-late-pass] Returns the shared paused byte used by level update, pause rendering, and screen-tint decay.
char __cdecl rf_game_pause_gate_query()
{
  return rf_game_paused;
}

