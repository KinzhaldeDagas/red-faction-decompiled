// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058AC10 rf_mouse_set_absolute_xy_and_wheel
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Recovered cdecl(x,y,wheel). Enters mouse critical section UNCONDITIONALLY, delegates XY to cursor-warp/direct-cache setter, stores supplied wheel both as cached cumulative wheel-Z193A030 and message-wheel accumulator193A05C, leaves lock. No initialized guard, coordinate clamp or baseline/delta reset. In cursor mode cached XY is refreshed by later poll, not this setter.
void __cdecl rf_mouse_set_absolute_xy_and_wheel(int x, int y, int wheel)
{
  EnterCriticalSection(&unk_193A044);
  rf_mouse_set_cached_xy_or_warp_cursor(x, y);
  dword_193A030 = wheel;
  dword_193A05C = wheel;
  LeaveCriticalSection(&unk_193A044);
}

