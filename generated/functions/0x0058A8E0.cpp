// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A8E0 rf_mouse_set_bounds_and_reset
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): When initialized, under critical section stores width/height, sets cached XY to integer center and message wheel accumulator0, then polls and resets state (reset polls again). Does not validate dimensions, directly warp cursor, reset DirectInput interface or change centering gates. Nested helper locks use the same critical section.
void __cdecl rf_mouse_set_bounds_and_reset(int a1, int a2)
{
  if ( byte_193A06D )
  {
    EnterCriticalSection(&unk_193A044);
    dword_193A038 = a1;
    dword_193A034 = a2;
    dword_193A060 = a1 / 2;
    dword_193A040 = a2 / 2;
    dword_193A05C = 0;
    rf_mouse_poll_frame_snapshot_and_motion();
    rf_mouse_reset_buttons_and_motion();
    LeaveCriticalSection(&unk_193A044);
  }
}

