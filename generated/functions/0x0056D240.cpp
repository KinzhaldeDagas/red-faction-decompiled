// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D240 rf_frame_clock_get_time_divisor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl no args. Loads stored float663ED4 directly intoST0 and returns floating result. No reciprocal,clamp or initialization.
double __cdecl rf_frame_clock_get_time_divisor()
{
  return flt_663ED4;
}

