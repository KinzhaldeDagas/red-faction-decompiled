// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A510 rf_vector2_distance_squared_x87
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): cdecl(twoFloatA,twoFloatB). Forms B-A and returns x*x+y*y rounded to float then ST0 through558AD0. No sqrt; result remains live through epilogue, not void.
double __cdecl rf_vector2_distance_squared_x87(const float *a1, const float *a2)
{
  float *v2; // eax
  float v4[2]; // [esp+0h] [ebp-8h] BYREF

  v2 = rf_vector2_subtract_to_output((float *)a2, v4, (float *)a1);
  return rf_vector2_length_squared_x87(v2);
}

