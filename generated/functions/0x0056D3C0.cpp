// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D3C0 rf_frame_clock_history_get_biased_min_max
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl(outMin,outMax),nonnull outputs required. Initializes min=1.0,max=0.0,then scans history18092A0 indices0..min(SIGNED frameCounter18092E0,16)-1. Counter limit reloaded during loop. History contains limited but unscaled frame durations from56CFB0. No samples returns1/0; min remains1 if every duration>1 (possible with wide limit mode),max remains0 if all negative. No finite filtering,snapshot lock or general extrema initialization; outputs aliasing affects both comparisons.
void __cdecl rf_frame_clock_history_get_biased_min_max(float *a1, float *a2)
{
  int v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  *a1 = 1.0;
  *a2 = 0.0;
  for ( i = 0; ; ++i )
  {
    v2 = SLODWORD(flt_18092A0[16]) >= 16 ? 16 : LODWORD(flt_18092A0[16]);
    if ( i >= v2 )
      break;
    if ( *a2 < (double)flt_18092A0[i] )
      *a2 = flt_18092A0[i];
    if ( *a1 > (double)flt_18092A0[i] )
      *a1 = flt_18092A0[i];
  }
}

