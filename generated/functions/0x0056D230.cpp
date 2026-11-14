// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D230 rf_frame_clock_set_time_divisor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl(float divisor). Stores scalar directly at663ED4; frame update DIVIDES limited duration by it. No positivity,zero/finite guard,reset of history or update of current delta; values>1 slow effective time,values0 divide byzero on update.
void __cdecl rf_frame_clock_set_time_divisor(float divisor)
{
  flt_663ED4 = divisor;
}

