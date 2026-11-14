// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D250 rf_frame_clock_set_duration_limits_sorted
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl(float first,float second). If ordered second>first,stores min663ED8=first,max663EDC=second;otherwise stores min=second,max=first. Equality takes latter branch;unordered takes latter branch as well,so this is not a finite-validation routine. No positive-range clamp,unit conversion or current-delta/history update. Bounds are seconds per frame,not frames per second.
void __cdecl rf_frame_clock_set_duration_limits_sorted(float a1, float a2)
{
  if ( a2 <= (double)a1 )
  {
    flt_663ED8 = a2;
    flt_663EDC = a1;
  }
  else
  {
    flt_663ED8 = a1;
    flt_663EDC = a2;
  }
}

