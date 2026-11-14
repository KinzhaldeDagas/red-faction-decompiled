// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056ACB0 rf_aabb_overlap_inclusive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl(minA,maxA,minB,maxB). Returnsbyte1 iff maxB>=minA and minB<=maxA on eachXYZ axis. Touching faces/edges/points included; unordered comparisons reject. Does not normalize inverted bounds or expand by epsilon; no output/mutation.
bool __cdecl rf_aabb_overlap_inclusive(float *a1, float *a2, float *a3, float *a4)
{
  return *a4 >= (double)*a1
      && a4[1] >= (double)a1[1]
      && a4[2] >= (double)a1[2]
      && *a3 <= (double)*a2
      && a3[1] <= (double)a2[1]
      && a3[2] <= (double)a2[2];
}

