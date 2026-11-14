// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A950 rf_mouse_reset_buttons_and_motion
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): When initialized, polls frame first, then zeros relative deltas. Under lock for each of three records: clears SNAPSHOT double-click byte,release count,press count; resets PENDING deadline via clock offset0 and clears PENDING held byte. Does NOT clear snapshot held byte+0 after the just-completed copy, so it can retain prior held state until another poll. Does not reset cached XY, cumulative wheel coordinates or centering gates.
void rf_mouse_reset_buttons_and_motion()
{
  int i; // [esp+0h] [ebp-4h]

  if ( byte_193A06D )
  {
    rf_mouse_poll_frame_snapshot_and_motion();
    unk_193A078 = 0;
    unk_193A074 = 0;
    unk_193A070 = 0;
    EnterCriticalSection(&unk_193A044);
    for ( i = 0; i < 3; ++i )
    {
      unk_193A0B1[16 * i] = 0;
      dword_193A0B8[4 * i] = 0;
      unk_193A0B4[4 * i] = 0;
      rf_clock_deadline_set_wrapped_offset(&unk_193A08C[4 * i], 0);
      unk_193A080[16 * i] = 0;
    }
    LeaveCriticalSection(&unk_193A044);
  }
}

