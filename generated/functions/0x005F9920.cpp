// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F9920 rf_noise_gradient3_normalize_unchecked
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl mutable float[3]. float-rounded lengthSq=x*x+y*y+z*z,sqrt helper,float-rounded length;divides x/y/z,returns pointer. No zero/finite check or fallback;random all-zero gradient produces NaNs. Does not use general vector normalization helper.
float *__cdecl rf_noise_gradient3_normalize_unchecked(float *a1)
{
  float v2; // [esp+4h] [ebp-8h]
  float v3; // [esp+8h] [ebp-4h]

  v2 = *a1 * *a1 + a1[1] * a1[1] + a1[2] * a1[2];
  v3 = rf_sqrt_float(v2);
  *a1 = *a1 / v3;
  a1[1] = a1[1] / v3;
  a1[2] = a1[2] / v3;
  return a1;
}

