// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559A00 rf_triangle_unit_normal_from_three_points_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): cdecl FOUR stack arguments(output,p0,p1,p2); calls corrected559A30 cross(p1-p0,p2-p1) then reciprocal-sqrt normalizes output in place. Returns output. No zero-area/collinearity/NaN guard; degenerate triangle can produce NaN normal.
float *__cdecl rf_triangle_unit_normal_from_three_points_unchecked(
        float *a1,
        const float *a2,
        const float *a3,
        const float *a4)
{
  rf_triangle_cross_from_three_points(a1, a2, a3, a4);
  return rf_vector_normalize_reciprocal_sqrt(a1);
}

