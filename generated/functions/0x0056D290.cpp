// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D290 rf_frame_clock_get_duration_limits_optional
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl(outMin,outMax),each nullable. If outMin nonNULL copies float663ED8;if outMax nonNULL copies663EDC. If outputs alias,the max store wins. No mutation of settings,initialization or semantic return value; EAX incidental on paths.
void __cdecl rf_frame_clock_get_duration_limits_optional(float *out_min, float *out_max)
{
  if ( out_min )
    *out_min = flt_663ED8;
  if ( out_max )
    *out_max = flt_663EDC;
}

