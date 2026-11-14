// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A530 rf_mouse_initialize
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): If not initialized, sets initialized1, stores width193A038/height193A034, initializes and enters critical section193A044, initializes cached XY to center and message wheel accumulator0. Polls frame then resets buttons/motion (reset itself polls again). Attempts DirectInput initialization; failure selects cursor mode663F4C=1. Registers mouse window callback, leaves lock and registers shutdown via atexit. Existing initialized call does no work. No dimension validation; return is atexit result or prior initialized flag.
int __cdecl rf_mouse_initialize(int a1, int a2)
{
  int result; // eax

  result = (unsigned __int8)byte_193A06D;
  if ( !byte_193A06D )
  {
    byte_193A06D = 1;
    dword_193A038 = a1;
    dword_193A034 = a2;
    InitializeCriticalSection(&unk_193A044);
    EnterCriticalSection(&unk_193A044);
    dword_193A060 = dword_193A038 / 2;
    dword_193A040 = dword_193A034 / 2;
    dword_193A05C = 0;
    rf_mouse_poll_frame_snapshot_and_motion();
    rf_mouse_reset_buttons_and_motion();
    if ( rf_mouse_initialize_directinput8() == -1 )
      dword_663F4C = 1;
    rf_window_register_message_observer_unchecked((int)rf_mouse_window_message_callback);
    LeaveCriticalSection(&unk_193A044);
    return atexit(rf_mouse_shutdown);
  }
  return result;
}

