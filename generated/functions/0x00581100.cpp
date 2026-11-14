// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581100 rf_renderer_depth_fade_alpha8
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Recovered cdecl float depth,returns unsigned AL. Let F=18CD370,N=18CD37C. First ordered F<=depth returns0. Else ordered N>=depth returns255. Remaining ordinary interval computes float t=1-(depth-N)/(F-N),then truncates t*255 using temporary x87 round-toward-zero control word,returns low8bits. No clamp,far>near check or explicit equal-denominator guard. NaN reaches255 branch by original unordered-status tests. F/N are projection-scaled far/fade-start depths,not world distances;boundary precedence is far first.
unsigned __int8 __cdecl rf_renderer_depth_fade_alpha8(float a1)
{
  float v2; // [esp+Ch] [ebp-Ch]

  if ( flt_18CD370 <= (double)a1 )
    return 0;
  if ( flt_18CD37C >= (double)a1 )
    return -1;
  v2 = 1.0 - (a1 - flt_18CD37C) / (flt_18CD370 - flt_18CD37C);
  return (int)(v2 * 255.0);
}

