// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058AB60 rf_mouse_get_absolute_state
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Arguments3 DWORD output pointers. Enabled reads X0x193A060,Y0x193A040,raw button-state DWORD0x193A030,returns0. Disabled zeroes all3 outputs,returns-1. No pointer validation,lock or counter reset;does not read relative deltas.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): CORRECTION to older button-state wording: output3 from193A030 is cumulative WHEEL/Z POSITION, not a button bitmask. Cursor-mode poll assigns message wheel accumulator193A05C; DirectInput poll adds relative Z. Other two outputs are cached X193A060 and Y193A040. Initialized returns0; disabled writes all three0 and returns-1. No lock or pointer checks. Buttons are separate pending/snapshot16-byte records.
int __cdecl rf_mouse_get_absolute_state(_DWORD *a1, _DWORD *a2, _DWORD *a3)
{
  if ( byte_193A06D )
  {
    *a1 = dword_193A060;
    *a2 = dword_193A040;
    *a3 = dword_193A030;
    return 0;
  }
  else
  {
    *a3 = 0;
    *a2 = 0;
    *a1 = 0;
    return -1;
  }
}

