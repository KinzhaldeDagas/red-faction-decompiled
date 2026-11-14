// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559B40 rf_vector_dot_direction_between_points_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): cdecl(vector,pointA,pointB). Computes unit(pointB-pointA) using unchecked normalized-copy, then returns dot(vector,unitDirection) in ST0. Not void: the final dot result remains live through epilogue. Does not subtract pointA from the first vector, so not a general point-to-line distance. Coincident endpoints unguarded.
double __cdecl rf_vector_dot_direction_between_points_unchecked(const float *a1, const float *a2, const float *a3)
{
  float *v3; // eax
  float *v4; // eax
  float v6[3]; // [esp+0h] [ebp-18h] BYREF
  float out_vector[3]; // [esp+Ch] [ebp-Ch] BYREF

  v3 = rf_vector_subtract(a3, out_vector, a2);
  v4 = rf_vector3_normalized_copy_unchecked(v3, v6);
  return rf_vector_dot((float *)a1, v4);
}

