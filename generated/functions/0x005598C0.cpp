// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005598C0 rf_vector_distance_squared
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, boundary x87 failure reproduction, fixed stack ABI, line projection, exact PE thresholds and original bytes): Corrected saved VOID ABI to floating ST0 return,cdecl two3-float point pointers. Builds local A-B then forwards vector-length-squared40D1C0 ST0 unchanged;no sqrt,source writes or output vector argument. This missing return propagated a false incoming x87 parameter into GeoMod boundary helper5317F0. Existing short squared-distance comment retained. No own finite/overflow guard.
// [UnrealRed combat room owner 2026-11-12; verified original-byte ASM; corrected by route-geometry review 2026-11-12]5598C0 materializes A-B as THREE FLOAT component stores through vector_subtract, then forwards40D1C0 ST0 squared-length result unchanged.40D1C0 computes (x*x+y*y)+z*z in x87 and explicitly FSTP/FLD DWORD at40D1EF/40D1F2 before returning, so the final squared sum rounds to FLOAT32 and may underflow to0.4BC240 compares this returned value directly with0; preserving extra binary64 precision would differ from native for subnormal squared results.
double __cdecl rf_vector_distance_squared(const float *a1, const float *a2)
{
  float *v2; // eax
  float out_vector[3]; // [esp+0h] [ebp-Ch] BYREF

  v2 = rf_vector_subtract(a1, out_vector, a2);
  return rf_vector_length_squared(v2);
}

