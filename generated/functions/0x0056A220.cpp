// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056A220 rf_spheres_overlap_strict
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl(centerA,centerB,radiusA,radiusB),FOUR stack arguments; returnsAL byte boolean. Calls squared Euclidean distance then compares (radiusA+radiusB)^2>distanceSquared through x87. Exact external tangency and unordered comparisons false. Radius signs are unchecked and their sum is squared; no sqrt. Old two-argument void declaration suppressed both radii and the boolean; callers40F0D1/4BADB9/4CAC58 push16bytes and testAL.
unsigned __int8 __cdecl rf_spheres_overlap_strict(
        const float *center_a,
        const float *center_b,
        float radius_a,
        float radius_b)
{
  return (radius_a + radius_b) * (radius_a + radius_b) > rf_vector_distance_squared(center_a, center_b);
}

