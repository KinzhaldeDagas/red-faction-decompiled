// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056AD40 rf_aabb_contains_point_inclusive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients; native unordered behavior corrected2026-11-12): Cdecl(point,min,max). For X,Y,Z in order, rejects only ORDERED minComponent>pointComponent or ORDERED maxComponent<pointComponent; equal OR UNORDERED individual comparisons pass. Min-vs-point uses AH41/JZ; max-vs-point AH5/JNP, with final successful JP. Returns canonicalAL1 iff none of six comparisons rejects, elseAL0; upperEAX incidental. Both ordered bounds inclusive. No bound sorting,tolerance,finite or pointer validation. A NaN coordinate/bound bypasses its individual comparison; remaining ordered bounds still apply.
bool __cdecl rf_aabb_contains_point_inclusive(float *a1, float *a2, float *a3)
{
  return *a2 <= (double)*a1
      && *a3 >= (double)*a1
      && a2[1] <= (double)a1[1]
      && a3[1] >= (double)a1[1]
      && a2[2] <= (double)a1[2]
      && a3[2] >= (double)a1[2];
}

