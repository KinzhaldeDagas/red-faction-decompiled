// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D350 rf_frame_clock_pause_depth_decrement_and_resample
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl no args. Unconditionally decrements32bit pause-depth18092F4,then calls5673A0(1000000),stores sampled signed microseconds into lastQpcSample18092E8 and returns that sample,EAX is NOT updated pause depth. Resamples even when still nested-paused; prevents ordinary paused interval from contributing to next resumed delta. No underflow/ready/error guard; decrementing0 produces nonzero negative pause depth and keeps frame updates suppressed.
int __cdecl rf_frame_clock_pause_depth_decrement_and_resample()
{
  int result; // eax

  --dword_18092F4;
  result = rf_performance_clock_elapsed_scaled(1000000);
  dword_18092E8 = result;
  return result;
}

