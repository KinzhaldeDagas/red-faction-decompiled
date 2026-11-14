// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557610 rf_aabb_strictly_inside_bounds
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): For six-float innerBox(minXYZ,maxXYZ), requires both corners strictly between supplied outer min/max on all three axes. Boundary equality rejects. Used by merge before descending into existing children; no normalization of inverted boxes or explicit NaN handling.
bool __cdecl rf_aabb_strictly_inside_bounds(float *a1, float *a2, float *a3)
{
  if ( *a2 >= (double)*a1 )
    return 0;
  if ( *a3 <= (double)*a1 )
    return 0;
  if ( a2[1] >= (double)a1[1] )
    return 0;
  if ( a3[1] <= (double)a1[1] )
    return 0;
  if ( a2[2] >= (double)a1[2] )
    return 0;
  if ( a3[2] <= (double)a1[2] )
    return 0;
  if ( *a2 >= (double)a1[3] )
    return 0;
  if ( *a3 <= (double)a1[3] )
    return 0;
  if ( a2[1] >= (double)a1[4] )
    return 0;
  if ( a3[1] <= (double)a1[4] )
    return 0;
  if ( a2[2] < (double)a1[5] )
    return a3[2] > (double)a1[5];
  return 0;
}

