// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00492030 rf_multiplayer_game_mode_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Cdecl no arguments. Returns raw DWORD704ED4. No normalization,mode-range check,authority admission or state change. Callers distinguish values0,1,2 separately; this getter does not
// infer a different network runtime-mode byte.
int rf_multiplayer_game_mode_get()
{
  return unk_704ED4;
}

