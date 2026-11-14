// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058ADA0 rf_mouse_set_centering_disabled
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Stores permission byte193A06E=(callerByte==0) and returns that boolean. Thus nonzero disabled argument suppresses this centering gate; zero permits it. Does not alter request gate193A06F or perform any Windows cursor operation.
BOOL __cdecl rf_mouse_set_centering_disabled(char a1)
{
  unk_193A06E = a1 == 0;
  return a1 == 0;
}

