// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D3A0 rf_frame_clock_accumulator_suspend_depth_decrement
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl no args. Subtracts1 from32bit18092F8 and returns NEW count. Accumulation resumes only when exactly0; underflow from0 leaves negative nonzero depth and continues suppressing that accumulator. Does not alter frame-pause depth,settings,history or clock sample.
int rf_frame_clock_accumulator_suspend_depth_decrement()
{
  return --unk_18092F8;
}

