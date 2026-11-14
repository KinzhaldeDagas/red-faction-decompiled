// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005574C0 rf_face_aabb_strictly_inside_bounds
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Recovered cdecl3args(face,minXYZ,maxXYZ). Requires BOTH face AABB corners16/28 strictly between supplied min/max on all axes. Boundary equality rejects. Evaluates stored face box, not polygon corners/plane. No pointer validation or explicit NaN guard.
unsigned __int8 __cdecl rf_face_aabb_strictly_inside_bounds(const void *a1, const float *a2, const float *a3)
{
  if ( *a2 >= (double)*((float *)a1 + 4) )
    return 0;
  if ( *a3 <= (double)*((float *)a1 + 4) )
    return 0;
  if ( a2[1] >= (double)*((float *)a1 + 5) )
    return 0;
  if ( a3[1] <= (double)*((float *)a1 + 5) )
    return 0;
  if ( a2[2] >= (double)*((float *)a1 + 6) )
    return 0;
  if ( a3[2] <= (double)*((float *)a1 + 6) )
    return 0;
  if ( *a2 >= (double)*((float *)a1 + 7) )
    return 0;
  if ( *a3 <= (double)*((float *)a1 + 7) )
    return 0;
  if ( a2[1] >= (double)*((float *)a1 + 8) )
    return 0;
  if ( a3[1] <= (double)*((float *)a1 + 8) )
    return 0;
  if ( a2[2] < (double)*((float *)a1 + 9) )
    return a3[2] > (double)*((float *)a1 + 9);
  return 0;
}

