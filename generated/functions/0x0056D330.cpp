// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D330 rf_frame_clock_pause_depth_increment
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl no args. Adds1 to32bit pause-depth18092F4,stores and returns NEW count inEAX. Frame update skips whenever count!=0. No clock sample,saturation,balanced-call check or history reset. Previous inc_tmpoff runtime label was misleading.
int rf_frame_clock_pause_depth_increment()
{
  return ++dword_18092F4;
}

