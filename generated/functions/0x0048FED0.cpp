// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048FED0 rf_set_startup_session_flag
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl no arguments. Writes shared startup/session BYTE704E80=1 only. Does not start host/client networking,change runtime mode/authority or allocate player; session tick48F000
// treats ANY nonzero flag as enabled. Return void.
void rf_set_startup_session_flag()
{
  rf_startup_session_flag = 1;
}

