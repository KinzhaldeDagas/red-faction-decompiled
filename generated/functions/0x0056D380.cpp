// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D380 rf_frame_clock_accumulator_suspend_depth_increment
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl no args. Adds1 to32bit18092F8 and returns NEW count. This gates ONLY accumulation of scaled integer milliseconds into18092E4 in56CFB0; does not prevent frame-delta/history/FPS or game/unpaused-clock advance. No sample,reset or balancing guard; old inc_tmpoff label unrelated to actual role.
int rf_frame_clock_accumulator_suspend_depth_increment()
{
  return ++unk_18092F8;
}

