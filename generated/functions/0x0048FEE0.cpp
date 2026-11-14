// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048FEE0 rf_clear_startup_session_flag
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl no arguments. Writes shared startup/session BYTE704E80=0 only. Called by main-menu initialization and multiplayer teardown. No direct player/network deletion or runtime-mode
// write; disables future48F000 helper dispatch. Return void. Existing descriptive name preserved.
void rf_clear_startup_session_flag()
{
  rf_startup_session_flag = 0;
}

