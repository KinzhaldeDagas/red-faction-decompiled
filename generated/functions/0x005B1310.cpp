// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B1310 rf_aabb_include_point_min_else_max
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): For each axis: if currentMin>point sets min=point;ELSE if currentMax<point sets max=point. Does NOT independently update both bounds for one point. Correct for an already-valid box;invalid extrema initialization can remain invalid or miss maximum. Skinned collision5CF6A0 seeds minFLT_MAX/maxpositiveFLT_MIN and relies on this helper,so strictly decreasing points expose the issue. No pointer/NaN/min<=max check.
void __cdecl rf_aabb_include_point_min_else_max(float *a1, float *a2, float *a3)
{
  if ( *a1 <= (double)*a3 )
  {
    if ( *a2 < (double)*a3 )
      *a2 = *a3;
  }
  else
  {
    *a1 = *a3;
  }
  if ( a1[1] <= (double)a3[1] )
  {
    if ( a2[1] < (double)a3[1] )
      a2[1] = a3[1];
  }
  else
  {
    a1[1] = a3[1];
  }
  if ( a1[2] <= (double)a3[2] )
  {
    if ( a2[2] < (double)a3[2] )
      a2[2] = a3[2];
  }
  else
  {
    a1[2] = a3[2];
  }
}

