// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B14B0 rf_aabb_expand_along_displacement
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): For each axis,nonnegative displacement adds to max;negative displacement adds to min. Expands existing box to include its translated endpoint,returns max pointer if Z>=0 else min pointer (branch-dependent pointer). Does not translate both bounds or reorder invalid bounds. Used for swept sphere edge broadphase;no finite/pointer validation.
float *__cdecl rf_aabb_expand_along_displacement(float *a1, float *a2, float *a3)
{
  if ( *a3 >= 0.0 )
    *a2 = *a2 + *a3;
  else
    *a1 = *a1 + *a3;
  if ( a3[1] >= 0.0 )
    a2[1] = a2[1] + a3[1];
  else
    a1[1] = a1[1] + a3[1];
  if ( a3[2] >= 0.0 )
  {
    a2[2] = a2[2] + a3[2];
    return a2;
  }
  else
  {
    a1[2] = a1[2] + a3[2];
    return a1;
  }
}

